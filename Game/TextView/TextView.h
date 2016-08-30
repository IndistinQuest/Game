#pragma once

#include <Siv3D.hpp>
#include "../Drawable/Drawable.h"

class TextView
	:public Drawable
{
public:
	/// <summary>
	/// �P�����Â\������镶����
	/// </summary>
	/// <param name='text'> �\�����镶���� </param>
	/// <param name='pos'> �\���̈�̍���̍��W </param>
	/// <param name='width'> �\���̈�̕� </param>
	/// <param name='lines'> �ő�s�� </param>
	/// <param name='font'> �t�H���g </param>
	/// <param name='Interval'> ������ǉ�����Ԋu </param>
	TextView(const String& text, const Point& pos, const int width, const int lines, const Font& font, int IntervalIncrease=3,Color color = Palette::White);

	~TextView();

	/// <summary>
	/// �X�V����
	/// </summar>
	void update();

	/// <summary>
	/// �`�悷��
	/// </summary>
	void draw()const;

	/// <summary>
	/// �e�L�X�g��ύX����
	/// </summary>
	/// <param name='text'> �V�����\�����镶���� </param> 
	void setNewText(const String& text);

	/// <summary>
	/// �e�L�X�g���S�ĕ\������Ă��邩
	/// </summary>
	/// <returns>  </returns>
	bool isPlotAll()const;

	/// <summary>
	/// �S�Ẵe�L�X�g���\�����ꂽ��Ԃɂ���
	/// </summary>
	void setPlotAll();

	/// <summary>
	/// �������ǉ������Ԋu��ς���
	/// </summary>
	/// <param name='interval'>�ǉ�����Ԋu</param>
	void setIntervalIncrease(int interval);

	/// <summary>
	/// �f�o�b�O����`��̈��\������
	/// </summary>
	void debugDraw()const;

private:
	//�P������ǉ�
	void addCharacter();
	int getStrRigthPos();
private:
	String str_m;					//�\�����镶����
	Font font_m;					//�t�H���g
	Point pos_m;					//�`��ʒu(����)
	int PositionToBreak_m;			//����X���W���z����Ǝ������s����
	unsigned lines_m;				//���݂̍s��
	unsigned maxLines_m;			//�ő�s��
	unsigned count_m;				//���݂̕\��������
	bool isAutomaticLineBreak;		//�������s���邩
	unsigned IntervalIncrease_m;	//�����𑝂₷�Ԋu(�t���[��)
	Color color_m;					//�����F
};
