#ifndef COMPONENT3DINTERFACE_H
#define COMPONENT3DINTERFACE_H
#include "three-widget_global.h"
#include <QGLWidget>
#include <string>
#include <vector>
#include <map>

#define Interface struct

/************************************************************************
*为了兼容老版本而保留
************************************************************************/
class TW_LIBRARY M3DModelWidgetBase : public QGLWidget
{
public:
    M3DModelWidgetBase( QWidget *parent ): QGLWidget( parent ){}
    virtual ~M3DModelWidgetBase(){}
    virtual bool SetProperty(QString& sProperty, bool bIsOnline ){ return false;}
};

/************************************************************************
*为了兼容老版本而保留，此接口将要废弃
************************************************************************/
extern "C" TW_LIBRARY M3DModelWidgetBase * Get3DModePlugin( QWidget *parent = NULL );

namespace NCI {
    /************************************************************************
    *该接口用于3D组件在编辑或者展示的时候，向用户业务系统请求相关的数据
    *由用户实现此接口。3D组件在Contex接口中获取该接口的实例指针
    ************************************************************************/
    Interface DataService
    {
        /************************************************************************
        *用户实现execute方法，使得3D组件有能力获取业务系统的数据
        *@request 	request是json格式的一个字符串，用于在编辑态请求模型子部件的相关联的oid，
        *			或者在展示的时候通过oid请求oid关联的设备的当前值
        *@response 	response是json格式的一个字符串，根据request的请求内容返回相应的数据
        *note		request以及response数据格式见文档说明
        ************************************************************************/
        virtual void execute(const std::string& request, std::string& response)=0;
        virtual ~DataService(){}
    };

    /************************************************************************
    *用户实现Log接口，3D组件使用此接口记录日志，方便用户管理日志。
    *3D组件在Contex接口中获取该Log的实例指针
    ************************************************************************/
    Interface Log
    {

        enum LAYER
        {
            NCLL_ERROR=0,
            NCLL_WARNING,
            NCLL_INFO,
            NCLL_DEBUG
        };
        /************************************************************************
        *用户实现write方法，3D组件通过该方法记录日志信息
        *@layer 	layer用于对日志信息分级
        *@tag 		tag参数用于标记该日志的一个标签
        *@information 	具体的日志信息
        ************************************************************************/

        virtual void write(LAYER layer,const std::string tag,const std::string information)=0;

        virtual ~Log() {}
    };


    /************************************************************************
    *用户实现Context接口，3D组件使用此接口获取DataService实例，Log实例，
    *及模型文件和图片配置文件等资源文件所在的根路径
    ************************************************************************/
    Interface Context
    {
        /************************************************************************
        *用户实现此方法，获取模型文件和图片配置文件等资源文件所在的根路径
        ************************************************************************/
        virtual std::string resourcePath()=0;

        /************************************************************************
        *获取Log接口的实例
        ************************************************************************/
        virtual NCI::Log*  log()=0;

        /************************************************************************
        *获取DataService实例
        ************************************************************************/
        virtual NCI::DataService* service()=0;

        virtual ~Context(){}

    };



    /************************************************************************
    *NC3DPlayerWidget用于提供给用户展示3D模型，
    *用户通过Get3DPlayerWidget获取该CSNC3DPlayerWidget实例指针
    ************************************************************************/
    class   TW_LIBRARY NC3DPlayerWidget : public M3DModelWidgetBase
    {
    public:
         NC3DPlayerWidget( QWidget *parent ):
             M3DModelWidgetBase( parent ) {
         }

         virtual ~NC3DPlayerWidget() {}

        /************************************************************************
        *该方法用于配置3D的展示内容,在编辑及展示的时候，行为有所不同。在编辑的时候，
        *即isOnline为false时，将弹出一个配置界面，配置该模型的一些数据，配置完成后，
        *配置的信息将通过configInfo参数返回，用户需要将此信息保存起来。在展示的时候，
        *即isOnline为true时,不会弹出配置界面，将根据configInfo的配置信息展示模型
        *@configInfo 	上一次配置好的配置信息
        *@isOnline 		表明当前的意图是配置模型信息还是直接根据配置信息展示模型
        ************************************************************************/
        virtual bool configure(std::string& configInfo, bool isOnline ) { return false;}

        /************************************************************************
        *该方法用于指示是否需要向用户业务系统继续请求数据，然后刷新模型子部件。
        *@enable 	enable为true时，表面允许请求数据，然后根据数据内容刷新模型子部件的状态
        *			enable为false时，停止向业务系统请求数据刷新子部件
        ************************************************************************/
        virtual void setQueqryEnable(bool enable){}

    };
}

/************************************************************************
*
*即isOnline为false时，将弹出一个配置界面，配置该模型的一些数据，配置完成后，
*配置的信息将通过configInfo参数返回，用户需要将此信息保存起来。在展示的时候，
*即isOnline为true时,不会弹出配置界面，将根据configInfo的配置信息展示模型
*@configInfo 	上一次配置好的配置信息
*@isOnline 		表明当前的意图是配置模型信息还是直接根据配置信息展示模型
************************************************************************/
extern "C" TW_LIBRARY NCI::NC3DPlayerWidget * Get3DPlayerWidget(NCI::Context* context, QWidget *parent = NULL );

//销毁窗体回收资源
//widget 被销毁的窗体指针
extern "C" TW_LIBRARY void Destory3DPlayerWidget(NCI::NC3DPlayerWidget *widget);

//测试指定窗体的动画
//widget 被测试的窗体指针
extern "C" TW_LIBRARY void TestAnimations(NCI::NC3DPlayerWidget *widget);

//高亮显示指定窗体的模型
//widget 被指定的窗体指针
//name 模型名
extern "C" TW_LIBRARY void LookingForAnimatingModel(NCI::NC3DPlayerWidget *widget,QString name);

//打开场景模型
//widget 被指定的窗体指针
//path 模型路径
//bckgroundImagePath 背景图片,可以传""
extern "C" TW_LIBRARY void OpenScene(NCI::NC3DPlayerWidget *widget,QString path,std::string backgroundImagePath);
extern "C" TW_LIBRARY void CloseScene(NCI::NC3DPlayerWidget *widget);

#endif // COMPONENT3DINTERFACE_H
