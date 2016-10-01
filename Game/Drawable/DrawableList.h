#pragma once

#include <map>
#include <memory>
#include <algorithm>
#include "Drawable.h"

class DrawableList
{
private:
    std::multimap<int, std::shared_ptr<Drawable>> m_drawables;
public:
    /// <summary>
    /// �R���X�g���N�^
    /// </summary>
    DrawableList() = default;

    /// <summary>
    /// �f�X�g���N�^
    /// </summary>
    ~DrawableList();

public:
    /// <summary>
    /// �`�惊�X�g�ɒǉ�����
    /// </summary>
    /// <param name="drawable"> �`�悷��I�u�W�F�N�g </param>
    /// <param name="layer"> ���C���[�ԍ� </param>
    void add(std::shared_ptr<Drawable> drawable, int layer);

    /// <summary>
    /// �S�ẴI�u�W�F�N�g��`�悷��
    /// </summary>
    void drawAll() const;
};

