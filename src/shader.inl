#pragma data_seg(".vsh")
static const char *vsh = \
"version 430\n"

"layout (location=0) in vec3 aPos;"
"out vec2 px;"
"void main()"
"{"
	"gl_Position=vec4(aPos, 1.0);"
	"px = aPos.xy;"
"}";

#pragma data_seg(".fsh") 
static const char *fsh = \
"#version 430\n"

"out vec4 FragColor"
"in vec2 px;"

"uniform vec4 fpar4[4];"

"int XRES = 1280;"
"int YRES = 720;"
"float EPSILON = 0.01;"

"float sdfSphere(vec3 p, float r)"
"{"
	"return length(p) - r;"
"}"

"float sdfScene(vec3 p)"
"{"
	"// infinite 3D domain repition"
	"p.x = mod(p.x+1.0, 2.0) - 1.0;"
	"p.y = mod(p.y+1.0, 2.0) - 1.0;"
	"p.z = mod(p.Z+1.0, 2.0) - 1.0;"

	"float d = sdfSphere(p, 0.5);"
	"return d;"
"}"

"vec3 estimateSdfNormal(vec3 p)"
"{"
	"return normalize(vec3("
		"sdfScene(vec3(p.x + EPSILON, p.y, p.z)) - sdfScene(vec3(p.x - EPSILON, p.y, p.z)),"
		"sdfScene(vec3(p.x, p.y + EPSILON, p.z)) - sdfScene(vec3(p.x, p.y - EPSILON, p.z)),"
		"sdfScene(vec3(p.x, p.y, p.z + EPSILON)) - sdfScene(vec3(p.x, p.y, p.z - EPSILON))"
	"));"
"}"

"vec3 simpleLambert(vec3 normal, vec3 col)"
"{"
	"vec3 lightDir = vec3(1.0, 2.0, 4.0);"
	"vec3 lightCol = vec3(1.0, 1.0, 1.0);"

	"float NdotL = max(dot(normal, lightDir), 0);"
	"vec3 c = vec3(col * lightCol * NdotL);"

	"return c;"
"}"

"void main()"
"{"
	"// uv are fragcoords (pixels) mapped from [xres, yres] to [0, 1]"
	"vec2 uv = px.xy /* / vec2(XRES, YRES))*/ * vec2(1.7777, 1.0);"

	"vec3 cameraPos = vec3(0, 1.0, -4.0);"
	"vec3 target = vec3(0);"

	"vec3 w = normalize(cameraPos - target);"
	"vec3 u = normalize(cross(w, vec3(0.0, 1.0, 0.0)));"
	"vec3 v = cross(u, w);"

	"vec3 rayOrigin = cameraPos;	// send rays from camera location"
	"vec3 rayDir = normalize(uv.x * u + uv.y * v + 0.75*w);	// send one ray per pixel 1.0 clip units into the scene"

	"float rayDepth = 0.0;"
	"vec3 col = vec3(0.2, 0.2, 0.2);"

	"for(int i = 0; i < 100; i++)	// send 100 rays total from camera into scene"
	"{"
		"float d = sdfScene(rayOrigin + rayDepth * rayDir);"

		"if(d < EPSILON)"
		"{"
			"col = simpleLambert(estimateSdfNormal(rayOrigin + rayDepth * rayDir), vec3(0.2, 0.2, 0.8));"
			"break;"
		"}"

		"rayDepth += d;"
		"if(rayDepth >= 100)"
		"{"
			"col = vec3(0.2, 0.2, 0.2);"
		"}"
	"}"
	"FragColor = vec4(col, 1.0);"
"}";

/*
static const char * fsh = \
"#version 430\n"

"layout (location=0) uniform vec4 fpar[4];"
"layout (location=0) out vec4 co;"
"in vec2 p;"

"float iSphere(in vec3 ro, in vec3 rd, in vec4 sph)"
"{"
    "vec3  q = ro - sph.xyz;"
    "float b = dot( q, rd );"
    "float c = dot( q, q ) - sph.w*sph.w;"
    "float h = b*b - c;"
    "if( h>0.0 ) h = -b - sqrt( h );"
	"return h;"
"}"

"void main()"
"{"
    "vec3 w=normalize(fpar[1].xyz-fpar[0].xyz);"
    "vec3 u=normalize(cross(w,vec3(0.0,1.0,0.0)));"
    "vec3 v=cross(u,w);"

    "vec3 ro = fpar[0].xyz;"
	"vec3 rd = normalize( p.x*u*1.77 + p.y*v + 0.75*w );"

    "float dif = dot( p, vec2(0.707) );"

    "float t = iSphere(ro,rd,fpar[2]);"
    "if(t>0.0)"
    "{"
        "vec3 pos = ro + t*rd;"
        "vec3 nor = normalize( pos - fpar[2].xyz );"
        "dif = dot(nor,vec3(0.57703));"
    "}"
    "co = dif*vec4(0.5,0.4,0.3,0.0) + vec4(0.5,0.5,0.5,1.0);"
"}";*/