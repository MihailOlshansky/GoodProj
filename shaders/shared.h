#ifdef __cplusplus
#include "Dev.h"
using float2 = DirectX::XMFLOAT2;
using float3 = DirectX::XMFLOAT3;
using float4 = DirectX::XMFLOAT4;
using float4x4 = DirectX::XMFLOAT4X4;

using uint =  uint32_t;
using uint2 = DirectX::XMUINT2;
using uint3 = DirectX::XMUINT3;
using uint4 = DirectX::XMUINT4;

#define SHADER_CB_SLOT(val) val
#define SHADER_SRV_SLOT(val) val
#define SHADER_SAMPLER_SLOT(val) val

#else
	struct VSDefaultIn {
		float3 pos : POSITION;
		float3 normal : NORMAL;
		float2 texCoord : TEXCOORD;
	};

#define SHADER_CB_SLOT(val) b ## val
#define SHADER_SRV_SLOT(val) t ## val
#define SHADER_SAMPLER_SLOT(val) s ## val

#endif

#define PER_FRAME_CB_SLOT SHADER_CB_SLOT(0)
#define PER_MESH_CB_SLOT SHADER_CB_SLOT(1)
#define PER_MATERIAL_CB_SLOT SHADER_CB_SLOT(2)
#define TONEMAPPING_CB_SLOT SHADER_CB_SLOT(3)

#define TEXTURE_COLOR_SRV_SLOT SHADER_SRV_SLOT(0)

#define LINEAR_SAMPLER_SLOT SHADER_SAMPLER_SLOT(0)
#define NEAREST_SAMPLER_SLOT SHADER_SAMPLER_SLOT(1)

struct TriangleData
{
	float3 color1;
	float _dummy1;
	float3 color2;
	float _dummy2;
	float3 color3;
	float _dummy3;
};

struct PerMaterialData
{
	float4 color;

	uint4 usedTextures;
};

struct PerFrameData
{
	float4x4 viewProj;
};

struct PerMeshData
{
	float4x4 transform;
};

struct ToneMappingCB
{
	float avgBrightnessLog;
	uint _padding[3];
};