#version 330 core
layout(location=0) in vec3 positionValue;
layout(location=1) in vec3 colorValue;
out vec3 fragValue;
uniform mat4 transform;
void main(){
//	gl_Position = vec4(positionValue.x, positionValue.y, positionValue.z, 1.0);
	gl_Position = transform*vec4(positionValue, 1.0);
	fragValue=colorValue;
}
