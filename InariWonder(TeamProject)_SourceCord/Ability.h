#pragma once

#ifndef FOX_ABILITY_H
#define FOX_ABILITY_H

#include "main.h"
#include "FieldObjectManager.h"
#include "texture.h"
#include "Fox.h"




///
///  �񋓑�
/// 

typedef enum ABILITY_KIND {
	ABILITY_MIKO_HEAL,			//�ޏ��̉�
	ABILITY_MIKO_ATTACK,		//�U���H
	ABILITY_MIKO_SHIELD,		//1��_���[�W����
	ABILITY_FOX_FIRE,			//�L�c�l�̉�
	ABILITY_FOX_ICE,			//�L�c�l�̕X

	ABILITY_MAX
}ABILITY_KIND;


class Ability
{
public:
	Ability() : _IsActive (false) {};
	~Ability();

	void SetIsActive(bool is)	{ _IsActive = is; }				//�ł���΂���܂�g�������Ȃ��A�ł��M�~�b�N�Ƃ��Ĕ\�͂𕕂���̂��g������
	bool GetIsActive()			{ return _IsActive; }

	//�A�r���e�B�g�p�҂ƃ^�[�Q�b�g�A�G�̏ꏊ�Ƃ��}�E�X�J�[�\���̈ʒu�Ȃǂ������ŗ^���Ďg�p����
	//�ړ�����̂ł��������A���̏�̂Ɏc��̂ł�����
	virtual void UseAbility(const OBJECT_DATA od,const D3DXVECTOR2& target) = 0;

	virtual void Update() = 0;									//�\�͕ʂŋ������ς��\��������@�ړ�������Ȃ�
			
	virtual void Draw() = 0;									//�A�r���e�B�̃t�B�[���h�I�u�W�F�N�g��̌�����

	//�ς̌����ڂ��ς�邩������Ȃ�����	����͓��t��������g��Ȃ��Ǝv��
	TEXTURE_DATA GetFoxAbilityTexture() {};
	
	void SetFieldObjectManagerPoint(FieldObjectManager* fOManager) { if (_FOManager == nullptr)_FOManager = fOManager; }		//���g�������ĂȂ�����������

private:
	//Ability();									//��{�g�킹�Ȃ�

protected:
	bool _IsActive;									//�\�͂��g�����Ԃ��H�@�������Ă��邩�ǂ����Ƃ�

	int _COOL_TIME;									//�A�r���e�B�g�p���Ă������1�x�g����悤�ɂȂ�܂ł̎���	�ޏ��̏ꍇ�̓A�C�e�����Ȃ邩��g��Ȃ������@���̕ϐ����̂܂܃X�L���̃X�^�b�N���Ƃ��Ďg���Ă�����
	int _Time;

	//template<typename T>T _TexData;				//�A�r���e�B���ƂɌŒ�̉摜�@typeid�Ō^�𒲂ׂāAInt��TEXDATA���m�F����
	TEXTURE_DATA* _TexData = nullptr;

	static FieldObjectManager* _FOManager;			//������g�p���ăt�B�[���h��ɃA�r���e�B�̃I�u�W�F�N�g�𐶐�����
};

#endif // !FOX_ABILITY_H