#include "IG2Object.h"
#include "Laberinto.h"
#include "Bloque.h";

// Init the static vector for listeners
std::vector<IG2Object*> IG2Object::appListeners = std::vector<IG2Object*>(0, nullptr);


//Constructoras
IG2Object::IG2Object() : mNode(nullptr), mSM(nullptr){
    this->initialPosition = Vector3::ZERO;
}

IG2Object::IG2Object(Vector3 initPos, SceneNode *node, SceneManager* sceneMng): initialPosition(initPos), mNode(node), mSM(sceneMng){
    this->setPosition(initialPosition);

    mNode = node;
    dir = Vector3(0, 0, 0);
    proxDir = Vector3(0, 0, 0);
}

IG2Object::IG2Object(Vector3 initPos, SceneNode *node, SceneManager* sceneMng, String mesh): initialPosition(initPos), mNode(node), mSM(sceneMng){
    
    // Creates a new entity with the mesh and attach the entity
    entity = sceneMng->createEntity(mesh);
    mNode->attachObject(entity);
    this->setPosition(initialPosition);

    mNode = node;
    dir = Vector3(0, 0, 0);
    proxDir = Vector3(0, 0, 0);
}

//Destructoras
IG2Object::~IG2Object() {
    
    this->removeEntity();
    
    if (mNode != nullptr){
        mSM->destroySceneNode(mNode);
        mNode = nullptr;
    }
    
    mSM = nullptr;
}


void IG2Object::setInitialPosition (Vector3 v){
    this->initialPosition = v;
}

void IG2Object::move (Vector3 v){
    mNode->translate(v);
}

void IG2Object::setPosition(Vector3 v){
    mNode->setPosition(v);
}

Vector3 IG2Object::getPosition (){
    return mNode->getPosition();
}

void IG2Object::setScale(Vector3 vScale){
    mNode->setScale(vScale);
}

void IG2Object::setVisible (bool visible){
    mNode->setVisible(visible);
}

Vector3 IG2Object::getOrientation (){    
    Vector3 result = mNode->_getDerivedOrientation() * Vector3::UNIT_Z;
    return (Vector3(trunc (result.x), trunc (result.y), trunc (result.z)));
}

void IG2Object::setMaterialName (string materialName){
    entity->setMaterialName(materialName); 
}

void IG2Object::setEntity(Entity* ent)
{
    entity = ent;
}

bool IG2Object::hasEntity (){
    return (entity != nullptr);
}

void IG2Object::removeEntity (){
    
    if (hasEntity() && (entity != nullptr)){
        mSM->destroyEntity(entity);
        entity = nullptr;
    }
}

Vector3 IG2Object::calculateBoxSize (){
        
    Vector3 result;    
    
    if (mNode->getAttachedObjects().size() > 0){
        Entity* mEntity = static_cast<Entity*>(mNode->getAttachedObject(0));
        const AxisAlignedBox& aab = mEntity->getBoundingBox();
        Vector3 min = aab.getMinimum()*mNode->getScale();
        Vector3 max = aab.getMaximum()*mNode->getScale();
        Real paddingFactor = MeshManager::getSingleton().getBoundsPaddingFactor();
        
        // adjust min & max to exclude the padding factor..
        Vector3 newMin = min+(max-min)*paddingFactor;
        Vector3 newMax = max+(min-max)*paddingFactor;
        result = newMax-newMin;
    }
    else
        result = {0,0,0};
    
    return result;
}

void IG2Object::entityMovement(Vector3 newDir)
{
    //Si está en el centro comprobamos las cosas
    if (Centre()) {
        Bloque* b = lab->getBloque(mNode->getPosition() + (proxDir * 100), 0, lab->getLenght() - 1);
        proxBlock = b;

        //la direccion debe cambiar, y el bloque es traspasable, giramos
        if (dir != proxDir) {

            if (b == nullptr || b->getTraspasable()) {
                dir = proxDir;

                Quaternion q = this->getOrientation().getRotationTo(dir);
                mNode->rotate(q, Ogre::Node::TS_LOCAL);
            }
        }
        else {

            if (b != nullptr && b->getTraspasable() == false) {

                dir = Vector3(0, 0, 0);
                proxDir = Vector3(0, 0, 0);
            }
        }
    }
}

bool IG2Object::Centre()
{
    int x, y, z;
    x = mNode->getPosition().x;
    y = mNode->getPosition().y;
    z = mNode->getPosition().z;

    Vector3 centro(x % 100, y % 100, z % 100);

    //Si todos los numeros son multiplos de 100 esta en un centro
    return centro == Vector3().ZERO;
}



const AxisAlignedBox& IG2Object::getAABB(){    
    return mNode->_getWorldAABB();
}

