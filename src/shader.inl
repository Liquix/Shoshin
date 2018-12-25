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

"out vec4 FragColor;"
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
	"p.x = mod(p.x+1, 2) - 1;"
	"p.y = mod(p.y+1, 2) - 1;"
	"p.z = mod(p.z + 1, 2) - 1;"
	"float d = sdfSphere(p, 0.5);"
	"return d;"
"}"

"vec3 estimateSdfNormal(vec3 p)"
"{"
	"return normalize(vec3(sdfScene(vec3(p.x + EPSILON, p.y, p.z)) - sdfScene(vec3(p.x - EPSILON, p.y, p.z)), sdfScene(vec3(p.x, p.y + EPSILON, p.z)) - sdfScene(vec3(p.x, p.y - EPSILON, p.z)), sdfScene(vec3(p.x, p.y, p.z + EPSILON)) - sdfScene(vec3(p.x, p.y, p.z - EPSILON))));"
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
	"vec2 uv = px * vec2(1.7777, 1.0);"
	"vec3 cameraPos = vec3(1.0 + 4.0*sin(fpar4[0][0]), 2.0*cos(fpar4[0][0]), -4.0);"
	//"vec3 cameraPos = vec3(0, 1.0, -4.0);"
	"vec3 target = vec3(0);"

	"vec3 w = normalize(cameraPos - target);"
	"vec3 u = normalize(cross(w, vec3(0.0, 1.0, 0.0)));"
	"vec3 v = cross(u, w);"

	"vec3 rayOrigin = cameraPos;"
	"vec3 rayDir = normalize(uv.x * u + uv.y * v + 0.75*w);"

	"float rayDepth = 0.0;"
	"vec3 col = vec3(0.2, 0.2, 0.2);"

	"for(int i = 0; i < 100; i++)"
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
	//"vec3 col = vec3(0, 0, 0.5);"
	"FragColor = vec4(col, 1.0);"
"}";

/*
"#version 430\n"

"out vec4 FragColor;"
"in vec2 px;"

"void main()"
"{"
"FragColor = vec4(0.0, 0.0, 1.0, 1.0);"
"}"; */