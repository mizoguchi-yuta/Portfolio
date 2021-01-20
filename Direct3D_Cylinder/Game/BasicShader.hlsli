cbuffer ConstantBuffer {
	matrix World; //���[���h�ϊ��s��
	matrix View; //�r���[�ϊ��s��
	matrix Projection; //�����Ήe�ϊ��s��
	matrix WorldViewProjection; //WVP�s��
};

//���_�V�F�[�_�[�ւ̓���
struct VSInput {
	float4 position: POSITION;
	float4 normal : NORMAL;
};

//���_�V�F�[�_�[����̏o��
struct VSOutput {
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

//�W�I���g���V�F�[�_�[�ւ̓���
typedef VSOutput GSInput;

//�W�I���g���V�F�[�_�[����̓���
struct GSOutput {
	float4 position : SV_POSITION;
	float4 color : COLOR0;
};

//�s�N�Z���V�F�[�_�[�ւ̓���
typedef GSOutput PSInput;