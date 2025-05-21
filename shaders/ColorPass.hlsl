#include "shaders/shared.h"

cbuffer PerFrame : register(PER_FRAME_CB_SLOT)
{
	PerFrameData frameData;
}

cbuffer PerMesh : register(PER_MESH_CB_SLOT)
{
	PerMeshData meshData;
}

cbuffer PerMaterial : register(PER_MATERIAL_CB_SLOT)
{
	PerMaterialData materialData;
}

Texture2D TextureColor : register(TEXTURE_COLOR_SRV_SLOT);

SamplerState LinearSampler : register(LINEAR_SAMPLER_SLOT);
SamplerState NearestSampler : register(NEAREST_SAMPLER_SLOT);

struct VSOut {
	float4 pos : SV_POSITION;
	float3 worldPos : WORLD_POSITION;
	float3 normal : NORMAL;
	float2 texCoord : TEX_COORD;
};

VSOut VSMain(VSDefaultIn input) {
	VSOut res;
	res.worldPos = mul(meshData.transform, float4(input.pos, 1)).xyz;
	res.pos = mul(frameData.viewProj, float4(res.worldPos, 1));
	res.normal = input.normal;
	res.texCoord = input.texCoord;
	return res;
}

float4 PSMain(VSOut input) : SV_TARGET{
	float4 color = materialData.color;
	if (materialData.usedTextures.x)
		color *= TextureColor.Sample(LinearSampler, input.texCoord);
	return color;
}