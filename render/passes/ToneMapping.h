#pragma once
#include "PassBase.h"

class ToneMappingPass : public PassBase {
private:
	Shader* toneMappingVertexShader;
	Shader* toneMappingPixelShader;
	ConstantBuffer<ToneMappingCB>* tonemapCB;
public:
	ToneMappingPass();

	virtual void init() override;
	virtual void process() override;

	virtual ~ToneMappingPass() override;
};