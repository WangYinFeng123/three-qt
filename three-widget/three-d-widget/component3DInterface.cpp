#include "threedwidget.h"
#include "extension/animationextension.h"
#include "../plugins/authorization.h"
#include "form/relavancedialog.h"

#include "json/reader.h"
#include "json/writer.h"
#include "json/value.h"
#include "component3DInterface.h"
using namespace NCI;

#include <QDialog>
#include <QString>
#include <QTimer>
#include <map>
#include <memory>
#include <iostream>
using namespace std;

struct Arguments {
    AnimationExtension ae;
    QMultiMap<QString,QString> animationNames;
    QTimer timer;
    Context* context;
    QString filePath;
    string imagePath;
    bool enableShadow;
};

static map<ThreeDWidget*,Arguments*> widgets;

void ThreeDWidget::updateModelStatus() {
    //cout << "updateModelStatus" << endl;
    Arguments* args = widgets[this];
    Json::Reader reader;
    Json::FastWriter writer;

    Json::Value lstObj;
    QStringList keys = args->animationNames.keys();
    for(QStringList::Iterator i=keys.begin();keys.end()!=i;i++) {
        QString oid = *i;
        Json::Value obj;
        obj["strApp"] = "scada";
        obj["strDb"] = "scada_model";
        obj["oid"] = oid.toLocal8Bit().data();
        lstObj.append(obj);
    }

    Json::Value reqObj;
    reqObj["strType"] = "query";
    reqObj["lstObj"] = lstObj;

    string req = writer.write(reqObj);
    string res;
    //res:{"lstObj":[{"data":{"dead":false,"manual":false,"value":1},"oid":"1001","strApp":"scada","strDb":"scada_model"}],"ret":1,"strType":"query"}
    //res:{"lstObj":[{"data":{"dead":false,"manual":false,"value":0},"oid":"1000","strApp":"scada","strDb":"scada_model"},{"data":{"dead":false,"manual":false,"value":1},"oid":"1001","strApp":"scada","strDb":"scada_model"}],"ret":2,"strType":"query"}

    NCI::DataService* cs = args->context->service();
    //cout << "excute:" << cs << endl;
    if(NULL == cs) return;
    //cout << "请求："<< req << endl;
    args->context->service()->execute(req,res);
    //cout << "响应：" << res << endl;

    Json::Value resObj;
    reader.parse(res,resObj);
    lstObj = resObj["lstObj"];

    int ret = resObj["ret"].asInt();
    if(ret == 0) cout << "数据获取失败!" << endl;

    QList<QMap<QString,QString> > details = sceneDetails();
    if(0 == details.size()) return;
    QMap<QString,QString> detail = details[0];

    for(Json::Value::iterator i=lstObj.begin();lstObj.end() != i;i++) {
        Json::Value obj = *i;
        if(obj["data"].isNull()) continue;
        QString oid = QString::fromLocal8Bit(obj["oid"].asCString());
        Json::Value data = obj["data"];

        for(QMap<QString,QString>::Iterator j=args->animationNames.find(oid);args->animationNames.end() != j;j++) {
            QString name = *j;
            double time = data["value"].asDouble();
            args->ae.update(detail,name,time);
        }
    }
}

void ThreeDWidget::requestOid(QString oid,QString& newOid,QString& description) {
    newOid = oid;
    Arguments* args = widgets[this];
    Json::Reader reader;
    Json::FastWriter writer;

    Json::Value reqObj,resObj;
    reqObj["strType"] = "info";
    reqObj["strApp"] = "scada";
    reqObj["strDb"] = "scada_model";
    reqObj["oid"] = oid.toLocal8Bit().data();

    string req = writer.write(reqObj);
    string res;
    NCI::DataService* cs = args->context->service();
    cout << "excute:" << cs << endl;
    if(NULL == cs) return;
    cout << "请求："<< req << endl;
    args->context->service()->execute(req,res);
    cout << "响应：" << res << endl;

    if(!reader.parse(res,resObj)) return;
    int ret = resObj["ret"].asInt();
    if(!ret) return;
    newOid = QString::fromLocal8Bit(resObj["oid"].asCString());
    description = QString::fromLocal8Bit(resObj["strName"].asCString());
}

/************************************************************************
*该方法用于指示是否需要向用户业务系统继续请求数据，然后刷新模型子部件。
*@enable 	enable为true时，表面允许请求数据，然后根据数据内容刷新模型子部件的状态
*			enable为false时，停止向业务系统请求数据刷新子部件
************************************************************************/
void ThreeDWidget::setQueqryEnable(bool enable)
{
    Arguments* w = widgets[this];
    QTimer& t = w->timer;
    QList<QMap<QString,QString> > details = this->sceneDetails();
    if(0 < details.size()) w->ae.stopAll(details[0]);
    if(t.isActive()) {
        cout << "setQueryEnable：停止定时器" << endl;
        t.stop();
        disconnect(&t,SIGNAL(timeout()),this,SLOT(updateModelStatus()));
    }

    if(enable) {
        cout << "setQueryEnable：启动定时器" << endl;
        connect(&t,SIGNAL(timeout()),this,SLOT(updateModelStatus()));
        //t.setSingleShot(true);
        t.start(2000);
    }
}

/************************************************************************
*该方法用于配置3D的展示内容,在编辑及展示的时候，行为有所不同。在编辑的时候，
*即isOnline为false时，将弹出一个配置界面，配置该模型的一些数据，配置完成后，
*配置的信息将通过configInfo参数返回，用户需要将此信息保存起来。在展示的时候，
*即isOnline为true时,不会弹出配置界面，将根据configInfo的配置信息展示模型
*@configInfo 	上一次配置好的配置信息
*@isOnline 		表明当前的意图是配置模型信息还是直接根据配置信息展示模型
************************************************************************/
bool ThreeDWidget::configure(std::string& configInfo, bool isOnline) {
    //{"bgImage":"","config":"/home/sl.truman/Desktop/5/build-NC3DWidget_test-Desktop_Qt_5_11_3_GCC_64bit-Debug/csnc-models/config/ZJJ-BaoTa-10kV.ncm.xml","modelName":"ZJJ-BaoTa-10kV.ncm"}
    Arguments* args = widgets[this];
    Json::Reader reader;
    Json::Value info;

    if(!reader.parse(configInfo,info)) {
        args->context->log()->write(Log::NCLL_INFO,"配置文件",configInfo);
        reader.parse("{\"bgImage\":\"\",\"config\":\"\",\"modelName\":\"\"}",info);
    }

    QString modelName = QString::fromLocal8Bit(info["modelName"].asCString());

    if (!isOnline) {
        RelavanceDialog dlg;
        connect(&dlg,SIGNAL(requestOid(QString,QString&,QString&)),this,SLOT(requestOid(QString,QString&,QString&)));
        dlg.workingDir = QString::fromLocal8Bit(args->context->resourcePath().data()) + "/CSNC/3DModels";
        dlg.modelName = modelName;
        args->context->log()->write(Log::NCLL_INFO,"模型目录",dlg.workingDir.path().toLocal8Bit().data());
        int dlgResult = dlg.exec();
        args->animationNames = dlg.animationNames;
        disconnect(&dlg,SIGNAL(requestOid(QString,QString&,QString&)),this,SLOT(requestOid(QString,QString&,QString&)));
        if (dlgResult == QDialog::Accepted)
            configInfo = QString("{\"bgImage\":\"\",\"config\":\"%1\",\"modelName\":\"%2\"}").arg(dlg.sceneFileName + ".xml").arg(dlg.sceneFileName).toLocal8Bit().data();

        return dlgResult;
    }

    string backImage = info["bgImage"].asString();
    QString configFilePath = QString::fromLocal8Bit(widgets[this]->context->resourcePath().data()) + "/CSNC/config/" + QString::fromLocal8Bit(info["config"].asCString());
    QString modelFilePath = QString::fromLocal8Bit(widgets[this]->context->resourcePath().data()) + "/CSNC/3DModels/" + modelName;
    args->context->log()->write(Log::NCLL_INFO,"模型文件",modelFilePath.toLocal8Bit().data());

    if(!configFilePath.isEmpty()) {
        QFile target(configFilePath);
        target.open(QFile::ReadOnly);
        QDomDocument doc;
        doc.setContent(target.readAll());
        target.close();
        QDomElement root = doc.documentElement();
        if(0 < root.childNodes().size()) {
            QDomNode nodes = root.childNodes().at(0);
            int count = nodes.childNodes().size();
            args->animationNames.clear();
            for(int i=0;i < count;i++) {
                QDomNode node = nodes.childNodes().at(i);
                args->animationNames.insertMulti(node.attributes().namedItem("oid").nodeValue(),node.attributes().namedItem("name").nodeValue());
            }
        }
    }

    if(modelFilePath == "") return false;
    args->filePath = modelFilePath;
    args->imagePath = backImage;
    args->enableShadow = false;
    return openScene(modelFilePath,backImage);
}

NCI::NC3DPlayerWidget * Get3DPlayerWidget(NCI::Context* context, QWidget *parent)
{
    Arguments* args = new Arguments();
    args->context = context;

    cout << "[Get3DPlayerWidget] 创建3D插件窗体" << endl;
    ThreeDWidget* w = new ThreeDWidget(parent);
    widgets.insert(make_pair(w,args));
    cout << "[Get3DPlayerWidget] 注册3D插件窗体" << endl;
    cout << "[Get3DPlayerWidget] 加载授权插件" << endl;

    if(!Authorization::verity()) {
        cerr << "[Get3DPlayerWidget] 授权验证失败，运行./config设置授权文件。" << endl;
        return NULL;
    }

    cout << "[Get3DPlayerWidget] 授权验证成功！" << endl;
    cout << "[Get3DPlayerWidget] 加载动画插件" << endl;
    w->addExtension(args->ae);

    //    args->pe.setPickedEvent([=](QMap<QString,QString> details) {
    //        args->detailForm.close();
    //        QString text;
    //        auto keys = details.keys();
    //        for(auto i = keys.begin();keys.end()!=i;i++) {
    //            auto k = *i;
    //            text += k + ":" + details[k] + '\n';
    //        }
    //        args->detailForm.setText(text);
    //        args->detailForm.move(w->cursor().pos());
    //        args->detailForm.show();
    //    });
    //    args->pe.setCanceledEent([=](){
    //        args->detailForm.close();
    //    });
    //    args->context->log()->write(Log::NCLL_INFO,"Get3DPlayerWidget","加载选择插件");
    //    w->addExtension(args->pe);

    return w;
}

void Destory3DPlayerWidget(NCI::NC3DPlayerWidget *widget) {
    map<ThreeDWidget*,Arguments*>::iterator it = widgets.find(dynamic_cast<ThreeDWidget*>(widget));
    if(it == widgets.end())
        return;
    Arguments* args = it->second;
    args->context->log()->write(Log::NCLL_INFO,"Destory3DPlayerWidget","销毁3D插件窗体");
    widgets.erase(dynamic_cast<ThreeDWidget*>(widget));
    delete widget;
    delete args;
}

void TestAnimations(NCI::NC3DPlayerWidget *widget) {
    ThreeDWidget* w = dynamic_cast<ThreeDWidget*>(widget);
    map<ThreeDWidget*,Arguments*>::iterator it = widgets.find(w);
    if(it == widgets.end())
        return;
    Arguments* args = it->second;
    args->context->log()->write(Log::NCLL_INFO,"TestAnimations","动画测试");
    QList<QMap<QString,QString> > ams = w->sceneDetails();
    if(0 == ams.size()) return;
    for(QMultiMap<QString,QString>::Iterator i=args->animationNames.begin();args->animationNames.end() != i ;i++ ) {
        args->context->log()->write(Log::NCLL_INFO,"播放",i.value().toLocal8Bit().data());
        args->ae.play(ams[0],i.value());
    }
}

void LookingForAnimatingModel(NCI::NC3DPlayerWidget *widget,QString name) {
    ThreeDWidget* w = dynamic_cast<ThreeDWidget*>(widget);
    map<ThreeDWidget*,Arguments*>::iterator it = widgets.find(w);
    if(it == widgets.end())
        return;
    Arguments* args = it->second;
    args->context->log()->write(Log::NCLL_INFO,"LookingForAnimatingModel","高亮动画模型");
    it->first->lookingFor(name);
}

void OpenScene(NCI::NC3DPlayerWidget *widget,QString path,string backgroundImagePath) {
    ThreeDWidget* w = dynamic_cast<ThreeDWidget*>(widget);
    map<ThreeDWidget*,Arguments*>::iterator it = widgets.find(w);
    if(it == widgets.end())
        return;
    Arguments* args = it->second;
    args->context->log()->write(Log::NCLL_INFO,"OpenScene","打开场景");
    it->first->openScene(path, backgroundImagePath);
}

void CloseScene(NCI::NC3DPlayerWidget *widget) {
    ThreeDWidget* w = dynamic_cast<ThreeDWidget*>(widget);
    map<ThreeDWidget*,Arguments*>::iterator it = widgets.find(w);
    if(it == widgets.end())
        return;
    Arguments* args = it->second;
    args->context->log()->write(Log::NCLL_INFO,"OpenScene","打开场景");
    it->first->closeScene();
}
