#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include "component.h"
#include <Qpainter>

class spriteComponent : public Component
{
public:
    explicit spriteComponent(class GameObject* gameObject=nullptr,int drawOrder=200);//100order为最底层
    virtual ~spriteComponent();

    //! 绘制函数
    virtual void Draw();
    //! 设置贴图
    virtual void SetTexture(QString imageLocation);
    //! 更新Update
    void Update()override;
    //! 贴图宽度的get
    int		getWidth() const;
    //! 贴图高度的get
    int		getHeight() const;
    //! 绘制顺序的get和set
    int		getDrawOrder() const;
    void	setDrawOrder(int order);

protected:
    QString imageLocation;  //!<    图形相对路径
    int		mDrawOrder;		//!<	绘制顺序
    int		mWidth;		//!<	贴图宽
    int		mHeight;		//!<	贴图高
signals:
};

#endif // SPRITECOMPONENT_H
