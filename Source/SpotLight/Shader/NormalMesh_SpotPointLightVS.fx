// ���_�V�F�[�_�[�̓���
struct VS_INPUT
{
	float4 Position        : POSITION ;     // ���W( ���[�J����� )
	float3 Normal          : NORMAL0 ;      // �@��( ���[�J����� )
	float4 Diffuse         : COLOR0 ;       // �f�B�t���[�Y�J���[
	float4 Specular        : COLOR1 ;       // �X�y�L�����J���[
	float4 TexCoords0      : TEXCOORD0 ;	// �e�N�X�`�����W
} ;

// ���_�V�F�[�_�[�̏o��
struct VS_OUTPUT
{
	float4 Position        : POSITION ;
	float4 Diffuse         : COLOR0 ;
	float4 Specular        : COLOR1 ;
	float2 TexCoords0      : TEXCOORD0 ;
} ;

// �}�e���A���p�����[�^
struct VS_CONST_MATERIAL
{
	float4 Diffuse ;                // �}�e���A���f�B�t���[�Y�J���[
	float4 Specular ;               // �}�e���A���X�y�L�����J���[
	float4 Power ;                  // �}�e���A���X�y�L�����n�C���C�g�̋���
} ;

// ���C�g�p�����[�^
struct VS_CONST_LIGHT
{
	float4 Position ;               // ���W( �r���[��� )
	float3 Direction ;              // ����( �r���[��� )
	float4 Diffuse ;                // �f�B�t���[�Y�J���[
	float4 Specular ;               // �X�y�L�����J���[
	float4 Ambient ;                // �A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z��������
	float4 Range_FallOff_AT0_AT1 ;  // x:�L������  y:�X�|�b�g���C�g�pFallOff  z:�����ɂ�錸�������p�p�����[�^�O  w:�����ɂ�錸�������p�p�����[�^�P
	float4 AT2_SpotP0_SpotP1 ;      // x:�����ɂ�錸�������p�p�����[�^�Q  y:�X�|�b�g���C�g�p�p�����[�^�O( cos( Phi / 2.0f ) )  z:�X�|�b�g���C�g�p�p�����[�^�P( 1.0f / ( cos( Theta / 2.0f ) - cos( Phi / 2.0f ) ) )
} ;



// C++ ���Őݒ肷��萔�̒�`
float4              cfAmbient_Emissive        : register( c1  ) ;		// �}�e���A���G�~�b�V�u�J���[ + �}�e���A���A���r�G���g�J���[ * �O���[�o���A���r�G���g�J���[
float4              cfProjectionMatrix[ 4 ]   : register( c2  ) ;		// �r���[�@�@���@�ˉe�s��
float4              cfViewMatrix[ 3 ]         : register( c6  ) ;		// ���[���h�@���@�r���[�s��
float4              cfTextureMatrix[ 3 ][ 2 ] : register( c88 ) ;		// �e�N�X�`�����W����p�s��
float4              cfLocalWorldMatrix[ 3 ]   : register( c94 ) ;		// ���[�J���@���@���[���h�s��
VS_CONST_MATERIAL   cfMaterial                : register( c11 ) ;		// �}�e���A���p�����[�^
VS_CONST_LIGHT      cfLight[ 2 ]              : register( c14 ) ;		// �X�|�b�g���C�g�ƃ|�C���g���C�g�̃p�����[�^


// main�֐�
VS_OUTPUT main( VS_INPUT VSInput )
{
	VS_OUTPUT VSOutput ;
	float4 lWorldPosition ;
	float4 lViewPosition ;
	float3 lWorldNrm ;
	float3 lViewNrm ;
	float3 lLightHalfVec ;
	float4 lLightLitParam ;
	float4 lLightLitDest ;
	float3 lLightDir ;
	float3 lLightTemp ;
	float lLightDistancePow2 ;
	float lLightGen ;
	float lLightDirectionCosA ;
	float4 lTotalDiffuse ;
	float4 lTotalSpecular ;


	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// ���[�J�����W�����[���h���W�ɕϊ�
	lWorldPosition.x = dot( VSInput.Position, cfLocalWorldMatrix[ 0 ] ) ;
	lWorldPosition.y = dot( VSInput.Position, cfLocalWorldMatrix[ 1 ] ) ;
	lWorldPosition.z = dot( VSInput.Position, cfLocalWorldMatrix[ 2 ] ) ;
	lWorldPosition.w = 1.0f ;

	// ���[���h���W���r���[���W�ɕϊ�
	lViewPosition.x = dot( lWorldPosition, cfViewMatrix[ 0 ] ) ;
	lViewPosition.y = dot( lWorldPosition, cfViewMatrix[ 1 ] ) ;
	lViewPosition.z = dot( lWorldPosition, cfViewMatrix[ 2 ] ) ;
	lViewPosition.w = 1.0f ;

	// �r���[���W���ˉe���W�ɕϊ�
	VSOutput.Position.x = dot( lViewPosition, cfProjectionMatrix[ 0 ] ) ;
	VSOutput.Position.y = dot( lViewPosition, cfProjectionMatrix[ 1 ] ) ;
	VSOutput.Position.z = dot( lViewPosition, cfProjectionMatrix[ 2 ] ) ;
	VSOutput.Position.w = dot( lViewPosition, cfProjectionMatrix[ 3 ] ) ;

	// ���_���W�ϊ� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )



	// ���C�g�̏��� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// �f�B�t���[�Y�J���[�ƃX�y�L�����J���[�̒~�ϒl�̏�����
	lTotalDiffuse  = float4( 0, 0, 0, 0 ) ;
	lTotalSpecular = float4( 0, 0, 0, 0 ) ;

	// �@�����r���[��Ԃ̊p�x�ɕϊ� =====================================================( �J�n )

	// ���[�J���x�N�g�������[���h�x�N�g���ɕϊ�
	lWorldNrm.x = dot( VSInput.Normal, cfLocalWorldMatrix[ 0 ].xyz ) ;
	lWorldNrm.y = dot( VSInput.Normal, cfLocalWorldMatrix[ 1 ].xyz ) ;
	lWorldNrm.z = dot( VSInput.Normal, cfLocalWorldMatrix[ 2 ].xyz ) ;

	// ���[���h�x�N�g�����r���[�x�N�g���ɕϊ�
	lViewNrm.x = dot( lWorldNrm, cfViewMatrix[ 0 ].xyz ) ;
	lViewNrm.y = dot( lWorldNrm, cfViewMatrix[ 1 ].xyz ) ;
	lViewNrm.z = dot( lWorldNrm, cfViewMatrix[ 2 ].xyz ) ;

	// �@�����r���[��Ԃ̊p�x�ɕϊ� =====================================================( �I�� )










	// �X�|�b�g���C�g�̏��� *************************************************************( �J�n )

	// ���C�g�����x�N�g���̌v�Z
	lLightDir = normalize( lViewPosition.xyz - cfLight[ 0 ].Position.xyz ) ;


	// �����E�X�|�b�g���C�g�����l�v�Z =======================================( �J�n )

	// ���������v�Z ------------------

	// ���_�ƃ��C�g�ʒu�Ƃ̋����̓������߂�
	lLightTemp = lViewPosition.xyz - cfLight[ 0 ].Position.xyz ;
	lLightDistancePow2 = dot( lLightTemp, lLightTemp ) ;

	// �������̌v�Z lLightGen = 1 / ( �����l0 + �����l1 * ���� + �����l2 * ( ���� * ���� ) )
	lLightGen = 1.0f / ( cfLight[ 0 ].Range_FallOff_AT0_AT1.z + cfLight[ 0 ].Range_FallOff_AT0_AT1.w * sqrt( lLightDistancePow2 ) + cfLight[ 0 ].AT2_SpotP0_SpotP1.x * lLightDistancePow2 ) ;

	// �X�|�b�g���C�g�����v�Z --------

	// ���C�g�����x�N�g���ƃ��C�g�ʒu���璸�_�ʒu�ւ̃x�N�g���̓���( ���� Cos a )���v�Z 
	lLightDirectionCosA = dot( lLightDir, cfLight[ 0 ].Direction ) ;

	// �X�|�b�g���C�g�����v�Z  pow( falloff, ( ( Cos a - Cos f ) / ( Cos q - Cos f ) ) )
	lLightGen *= saturate( pow( abs( max( lLightDirectionCosA - cfLight[ 0 ].AT2_SpotP0_SpotP1.y, 0.0f ) * cfLight[ 0 ].AT2_SpotP0_SpotP1.z ), cfLight[ 0 ].Range_FallOff_AT0_AT1.y ) ) ;

	// �L�������O�������猸�������ő�ɂ��鏈��
	lLightGen *= step( lLightDistancePow2, cfLight[ 0 ].Range_FallOff_AT0_AT1.x ) ;

	// �����E�X�|�b�g���C�g�����l�v�Z =======================================( �I�� )


	// ���C�g�f�B�t���[�Y�J���[�ƃ��C�g�X�y�L�����J���[�̊p�x�����v�Z =======( �J�n )

	// �@���ƃ��C�g�̋t�����x�N�g���Ƃ̓��ς� lLightLitParam.x �ɃZ�b�g
	lLightLitParam.x = dot( lViewNrm, -lLightDir ) ;

	// �n�[�t�x�N�g���̌v�Z norm( ( norm( ���_�ʒu���王�_�ւ̃x�N�g�� ) + ���C�g�̕��� ) )
	lLightHalfVec = normalize( normalize( -lViewPosition.xyz ) - lLightDir ) ;

	// �@���ƃn�[�t�x�N�g���̓��ς� lLightLitParam.y �ɃZ�b�g
	lLightLitParam.y = dot( lLightHalfVec, lViewNrm ) ;

	// �X�y�L�������˗��� lLightLitParam.w �ɃZ�b�g
	lLightLitParam.w = cfMaterial.Power.x ;

	// ���C�g�v�Z
	lLightLitDest = lit( lLightLitParam.x, lLightLitParam.y, lLightLitParam.w ) ;

	// ���C�g�f�B�t���[�Y�J���[�ƃ��C�g�X�y�L�����J���[�̊p�x�����v�Z =======( �I�� )


	// �J���[�v�Z ===========================================================( �J�n )

	// �f�B�t�[�Y���C�g�~�ϒl += �����E�X�|�b�g���C�g�p�x�����l * ( �f�B�t�[�Y�p�x�����v�Z���� * �}�e���A���f�B�t���[�Y�J���[ * ���C�g�̃f�B�t�[�Y�J���[ + ���C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z�������� )
	lTotalDiffuse += lLightGen * ( lLightLitDest.y * cfLight[ 0 ].Diffuse * cfMaterial.Diffuse + cfLight[ 0 ].Ambient ) ;

	// �X�y�L�������C�g�~�ϒl += �X�y�L�����p�x�����v�Z���� * �����E�X�|�b�g���C�g���� * ���C�g�̃X�y�L�����J���[
	lTotalSpecular += lLightGen * lLightLitDest.z * cfLight[ 0 ].Specular ;

	// �J���[�v�Z ===========================================================( �I�� )

	// �X�|�b�g���C�g�̏��� *************************************************************( �I�� )





	// �|�C���g���C�g�̏��� *************************************************************( �J�n )

	// ���C�g�����x�N�g���̌v�Z
	lLightDir = normalize( lViewPosition.xyz - cfLight[ 1 ].Position.xyz ) ;


	// ���������l�v�Z =======================================================( �J�n )

	// ���_�ƃ��C�g�ʒu�Ƃ̋����̓������߂�
	lLightTemp = lViewPosition.xyz - cfLight[ 1 ].Position.xyz ;
	lLightDistancePow2 = dot( lLightTemp, lLightTemp ) ;

	// �������̌v�Z lLightGen = 1 / ( �����l0 + �����l1 * ���� + �����l2 * ( ���� * ���� ) )
	lLightGen = 1.0f / ( cfLight[ 1 ].Range_FallOff_AT0_AT1.z + cfLight[ 1 ].Range_FallOff_AT0_AT1.w * sqrt( lLightDistancePow2 ) + cfLight[ 1 ].AT2_SpotP0_SpotP1.x * lLightDistancePow2 ) ;

	// �L�������O�������猸�������ő�ɂ��鏈��
	lLightGen *= step( lLightDistancePow2, cfLight[ 1 ].Range_FallOff_AT0_AT1.x ) ;

	// ���������l�v�Z =======================================================( �I�� )


	// ���C�g�f�B�t���[�Y�J���[�ƃ��C�g�X�y�L�����J���[�̊p�x�����v�Z =======( �J�n )

	// �@���ƃ��C�g�̋t�����x�N�g���Ƃ̓��ς� lLightLitParam.x �ɃZ�b�g
	lLightLitParam.x = dot( lViewNrm, -lLightDir ) ;

	// �n�[�t�x�N�g���̌v�Z norm( ( norm( ���_�ʒu���王�_�ւ̃x�N�g�� ) + ���C�g�̕��� ) )
	lLightHalfVec = normalize( normalize( -lViewPosition.xyz ) - lLightDir ) ;

	// �@���ƃn�[�t�x�N�g���̓��ς� lLightLitParam.y �ɃZ�b�g
	lLightLitParam.y = dot( lLightHalfVec, lViewNrm ) ;

	// �X�y�L�������˗��� lLightLitParam.w �ɃZ�b�g
	lLightLitParam.w = cfMaterial.Power.x ;

	// ���C�g�v�Z
	lLightLitDest = lit( lLightLitParam.x, lLightLitParam.y, lLightLitParam.w ) ;

	// ���C�g�f�B�t���[�Y�J���[�ƃ��C�g�X�y�L�����J���[�̊p�x�����v�Z =======( �I�� )


	// �J���[�v�Z ===========================================================( �J�n )

	// �f�B�t�[�Y���C�g�~�ϒl += �����E�X�|�b�g���C�g�p�x�����l * ( �f�B�t�[�Y�p�x�����v�Z���� * �}�e���A���f�B�t���[�Y�J���[ * ���C�g�̃f�B�t�[�Y�J���[ + ���C�g�̃A���r�G���g�J���[�ƃ}�e���A���̃A���r�G���g�J���[����Z�������� )
	lTotalDiffuse += lLightGen * ( lLightLitDest.y * cfLight[ 1 ].Diffuse * cfMaterial.Diffuse + cfLight[ 1 ].Ambient ) ;

	// �X�y�L�������C�g�~�ϒl += �X�y�L�����p�x�����v�Z���� * �����E�X�|�b�g���C�g���� * ���C�g�̃X�y�L�����J���[
	lTotalSpecular += lLightGen * lLightLitDest.z * cfLight[ 1 ].Specular ;

	// �J���[�v�Z ===========================================================( �I�� )

	// �|�C���g���C�g�̏��� *************************************************************( �I�� )


	// ���C�g�̏��� ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )




	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �J�n )

	// �f�B�t���[�Y�J���[ = �f�B�t���[�Y���C�g�~�ϒl + �}�e���A���̃A���r�G���g�J���[�ƃO���[�o���A���r�G���g�J���[����Z�������̂ƃ}�e���A���G�~�b�V�u�J���[�����Z��������
	VSOutput.Diffuse = lTotalDiffuse + cfAmbient_Emissive ;

	// �f�B�t���[�Y�A���t�@�̓}�e���A���̃f�B�t���[�Y�J���[�̃A���t�@�����̂܂܎g��
	VSOutput.Diffuse.w = cfMaterial.Diffuse.w ;

	// �X�y�L�����J���[ = �X�y�L�������C�g�~�ϒl * �}�e���A���̃X�y�L�����J���[
	VSOutput.Specular = lTotalSpecular * cfMaterial.Specular ;


	// �e�N�X�`�����W�ϊ��s��ɂ��ϊ����s�������ʂ̃e�N�X�`�����W���Z�b�g
	VSOutput.TexCoords0.x = dot( VSInput.TexCoords0, cfTextureMatrix[ 0 ][ 0 ] ) ;
	VSOutput.TexCoords0.y = dot( VSInput.TexCoords0, cfTextureMatrix[ 0 ][ 1 ] ) ;

	// �o�̓p�����[�^�Z�b�g ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++( �I�� )


	// �o�̓p�����[�^��Ԃ�
	return VSOutput ;
}

