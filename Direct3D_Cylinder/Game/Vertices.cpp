#include "Game.h"

namespace {
	const D3D11_INPUT_ELEMENT_DESC VertexPosition_InputElementDescs[1] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
	};

	const D3D11_INPUT_ELEMENT_DESC VertexPositionNormal_InputElementDescs[2] = {
		{"POSITION",0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",  0,DXGI_FORMAT_R32G32B32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
}

//���̒��_����D3D11_INPUT_ELEMENT_DESC�ŕ\�����z����擾
const D3D11_INPUT_ELEMENT_DESC* VertexPosition::GetInputElementDescs() {
	return VertexPosition_InputElementDescs;
}

//GetInputElementDescs()�֐��Ŏ擾�����z��̗v�f�����擾
UINT VertexPosition::GetInputElementDescsLength() {
	return ARRAYSIZE(VertexPosition_InputElementDescs);
}

//���̒��_����D3D11_INPUT_ELEMENT_DESC�ŕ\�����z����擾
const D3D11_INPUT_ELEMENT_DESC* VertexPositionNormal::GetInputElementDescs() {
	return VertexPositionNormal_InputElementDescs;
}

//GetInputElementDescs()�֐��Ŏ擾�����z��̗v�f�����擾
UINT VertexPositionNormal::GetInputElementDescsLength() {
	return ARRAYSIZE(VertexPositionNormal_InputElementDescs);
}