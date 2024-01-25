#version 330 core
layout(location=0) in vec3 positionValue;
layout(location=1) in vec3 colorValue;
out vec3 fragValue;
void main(){
	gl_Position = vec4(positionValue.xyz, 1.0);
	fragValue=colorValue;
}
