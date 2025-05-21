#include "render/Render.h"
#include "AvgBrightness.h"

AvgBrightnessPass::AvgBrightnessPass() {

}

void AvgBrightnessPass::init() {
	firstCopyVertexShader = render->getShaderManager()->getShader("shaders/FirstCopyAvgBrightnessPass.hlsl", Shader::Stage::Vertex);
	firstCopyPixelShader = render->getShaderManager()->getShader("shaders/FirstCopyAvgBrightnessPass.hlsl", Shader::Stage::Pixel);

	copyVertexShader = render->getShaderManager()->getShader("shaders/CopyAvgBrightnessPass.hlsl", Shader::Stage::Vertex);
	copyPixelShader = render->getShaderManager()->getShader("shaders/CopyAvgBrightnessPass.hlsl", Shader::Stage::Pixel);


	for (int i = 0; i < 10; i++)
	{
		TempMonoTextures[i] = render->getTextureManager()->addTexture(1 << i, 1 << i, std::string("Avg Brighness tex size ") + std::to_string(1 << i), 1, false, DXGI_FORMAT_R32_FLOAT, true, false, nullptr);
		TempMonoTargets[i] = render->getRenderTargetManager()->addRenderTarget(TempMonoTextures[i]);
	}
}

void AvgBrightnessPass::process() {
	render->BeginEvent(L"AvgBrightnessPass");
	
	// find appropriate level
	uint32_t highLevel = min(9, max(1, log2(min(render->getHDRTexture()->getWidth(), render->getHDRTexture()->getHeight()))));

	{
		render->BeginEvent(L"Copy HDR brightness");
		// set target 
		render->getRenderTargetManager()->reset();
		TempMonoTargets[highLevel]->setActive();
		render->getRenderTargetManager()->apply();

		// set shader
		firstCopyVertexShader->setActive();
		firstCopyPixelShader->setActive();

		// set samplers
		render->getTextureManager()->setSamplers(firstCopyVertexShader);
		render->getTextureManager()->setSamplers(firstCopyPixelShader);

		// set prev tex
		render->getHDRTexture()->setActive(firstCopyPixelShader, TEXTURE_COLOR_SRV_SLOT);
		
		// run shader
		render->getD3DDeviceContext()->Draw(6, 0);

		render->EndEvent();
	}

	render->BeginEvent(L"Downsample");
	for (int destLevel = highLevel - 1; destLevel >= 0; destLevel--)
	{
		render->BeginEvent((std::to_wstring(destLevel + 1) + L"->" + std::to_wstring(destLevel)).c_str());

		// set target 
		render->getRenderTargetManager()->reset();
		TempMonoTargets[destLevel]->setActive();
		render->getRenderTargetManager()->apply();

		// set shader
		copyVertexShader->setActive();
		copyPixelShader->setActive();

		// set samplers
		render->getTextureManager()->setSamplers(copyVertexShader);
		render->getTextureManager()->setSamplers(copyPixelShader);

		// set prev tex
		TempMonoTextures[destLevel + 1]->setActive(copyPixelShader, TEXTURE_COLOR_SRV_SLOT);

		// run shader
		render->getD3DDeviceContext()->Draw(6, 0);
		render->EndEvent();
	}
	render->EndEvent();

	render->EndEvent();

	render->setAvgBrightness(TempMonoTextures[0]);
}

AvgBrightnessPass::~AvgBrightnessPass() {
}

