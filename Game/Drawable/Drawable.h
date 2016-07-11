#pragma once

#include <Siv3D.hpp>

/// <summary>
/// �`�悷��I�u�W�F�N�g�̃C���^�[�t�F�[�X
/// </summary>
class Drawable
{
private:
    bool m_isVisible;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    Drawable();

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    virtual ~Drawable() = default;
public:
    /// <summary>
    /// �`�悷��
    /// </summary>
    virtual void draw() const = 0;
    
    /// <summary>
    /// �I�u�W�F�N�g��\������
    /// </summary>
    void show();

    /// <summary>
    /// �I�u�W�F�N�g���\���ɂ���
    /// </summary>
    void hide();

    /// <summary>
    /// �I�u�W�F�N�g�̕\����Ԃ��擾����
    /// </summary>
    /// <returns> �\����� </returns>
    bool isVisible() const;
};

