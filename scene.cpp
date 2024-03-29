/*******************************************************************************
* Description: 场景基类(涵盖所有场景)
* Author: Niu yi qun
* Creation date: 2019/7/8
* Last modified person: Niu yi qun
* Last modified date: 2019/7/8
******************************************************************************/
#include "product.h"

namespace Jinhui {
  /*
   * GraphicsScene
   */
  // cotr
  GraphicsScene::GraphicsScene(QObject* parent)
    :QGraphicsScene(parent) {}

  GraphicsScene::~GraphicsScene() {}

  /*
   * Channel32_Scene
   */
  // cotr
  Channel32_Scene::Channel32_Scene(QObject* parent)
    :GraphicsScene(parent) {}

  Channel32_Scene::~Channel32_Scene() {}
}
