#version 330 core
in vec3 fragValue;
out vec4 fragmentColor;
void main(){
	fragmentColor=vec4(fragValue, 1.0);
}