#include "render/Render.h"
#include "ToneMapping.h"

ToneMappingPass::ToneMappingPass() {

}

void ToneMappingPass::init() {
	toneMappingVertexShader = render->getShaderManager()->getShader("shaders/ToneMappingPass.hlsl", Shader::Stage::Vertex);
	toneMappingPixelShader = render->getShaderManager()->getShader("shaders/ToneMappingPass.hlsl", Shader::Stage::Pixel);
}

void ToneMappingPass::process() {
	render->BeginEvent(L"ToneMappingPass");
	
	// set target 
	render->getRenderTargetManager()->reset();
	render->getBackBufferTarget()->setActive();
	render->getRenderTargetManager()->apply();

	// set shader
	toneMappingVertexShader->setActive();
	toneMappingPixelShader->setActive();

	// set samplers
	render->getTextureManager()->setSamplers(toneMappingVertexShader);
	render->getTextureManager()->setSamplers(toneMappingPixelShader);

	// set prev tex
	render->getHDRTexture()->setActive(toneMappingPixelShader, TEXTURE_COLOR_SRV_SLOT);
	render->getAvgBrigtness()->setActive(toneMappingPixelShader, TEXTURE_AVG_BRIGHTNESS_SLOT);

	// run shader
	render->getD3DDeviceContext()->Draw(6, 0);


	render->EndEvent();
}

ToneMappingPass::~ToneMappingPass() {
}

