#version 330 core

struct line_data
{
	vec3 A; // MUST BE NORMALIZED!!
	vec3 ACrossB; // MUST BE NORMALIZED!!
	float ADotB;
};

in vec3 FragPos;
in vec3 SurfaceNormal;
in vec4 ObjectColor;

#define NUM_LINES 6
uniform line_data LineDatas[NUM_LINES];
uniform vec3 ViewPos;

out vec4 OutColor;

bool IsOnALine()
{
	for(int LineDataIndex = 0;
		LineDataIndex < NUM_LINES;
		++LineDataIndex)
	{
		line_data LineData = LineDatas[LineDataIndex];

		vec3 FragPosNormalized = normalize(FragPos);
		float FragPosDotACrossB = dot(FragPosNormalized, LineData.ACrossB);
		float MaxCosine = 0.0025f; // CAN ALSO BE LINE WIDTH!!
		if(abs(FragPosDotACrossB) < MaxCosine)
		{
			float ADotFragPos = dot(LineData.A, FragPosNormalized);
			if(ADotFragPos > LineData.ADotB)
			{
				vec3 ACrossFragPos = cross(LineData.A, FragPosNormalized);
				if(dot(ACrossFragPos, LineData.ACrossB) > 0.0f)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void main()
{
	vec4 FragmentColor = IsOnALine() ? vec4(1.0f, 1.0f, 1.0f, 1.0f) : ObjectColor;
	vec3 LightPos = vec3(-5.0f, 10.0f, 20.0f);
	vec3 LightColor = vec3(1.0f, 1.0f, 1.0f);

	vec3 Normal = normalize(SurfaceNormal);
	vec3 FromFragToLight = normalize(LightPos - FragPos);
	float MaxSpecular = 0.5f;
	vec3 ViewDir = normalize(ViewPos - FragPos);
	vec3 ReflectDir = reflect(-FromFragToLight, Normal);

	float SpecularStrength = pow(max(dot(ViewDir, ReflectDir), 0.0f), 32.0f);
	vec3 Specular = MaxSpecular * SpecularStrength * LightColor;

	float DiffuseScalar = max(dot(Normal, FromFragToLight), 0.0f);
	vec3 Diffuse = DiffuseScalar * LightColor;

	float AmbientStrength = 0.1f;
	vec3 Ambient = AmbientStrength * LightColor;

	vec4 Result = vec4(Ambient + Diffuse + Specular, 1.0f) * FragmentColor;
	OutColor = Result;
}
