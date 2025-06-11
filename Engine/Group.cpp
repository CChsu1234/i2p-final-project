#include <stdexcept>
#include <utility>

#include "Group.hpp"
#include "IControl.hpp"
#include "IObject.hpp"
#include "IObject3D.hpp"

namespace Engine {
    void Group::addObject(bool shouldDelete, IObject *obj) {
        objects.emplace_back(shouldDelete, obj);
        obj->objectIterator = std::prev(objects.end());
    }
    void Group::addObject3D(bool shouldDelete, IObject3D *obj3d) {
        object3ds.emplace_back(shouldDelete, obj3d);
        obj3d->object3DIterator = std::prev(object3ds.end());
    }
    void Group::addControl(bool shouldDelete, IControl *ctrl) {
        controls.emplace_back(shouldDelete, ctrl);
        ctrl->controlIterator = std::prev(controls.end());
    }
    void Group::insertObject(bool shouldDelete, IObject *obj, std::list<std::pair<bool, IObject *>>::iterator it) {
        objects.emplace(it, shouldDelete, obj);
        obj->objectIterator = std::prev(it);
    }
    Group::~Group() {
        Clear();
    }
    void Group::Clear() {
        for (auto &it : objects) {
            if (it.first) delete it.second;
        }
        objects.clear();
        for (auto &it : object3ds) {
            if (it.first) delete it.second;
        }
        object3ds.clear();
        for (auto &it : controls) {
            if (it.first) delete it.second;
        }
        controls.clear();
    }
    void Group::Update(float deltaTime) {
        for (auto it = objects.begin(); it != objects.end();) {
            auto preIt = it++;
            if (preIt->second->Visible)
                preIt->second->Update(deltaTime);
        }
        for (auto it = object3ds.begin(); it != object3ds.end();) {
            auto preIt = it++;
            if (preIt->second->Visible)
                preIt->second->Update(deltaTime);
        }
    }
    void Group::Transform() {
        for (auto &it : object3ds) {
            it.second->Transform();
        }
    }
    void Group::Draw() const {
        IObject3D::Draw();
        for (auto &it : objects) {
            if (it.second->Visible)
                it.second->Draw();
        }
    }
    void Group::CleanUp() {
        IObject3D::CleanUp();
    }
    void Group::OnKeyDown(int keyCode) {
        for (auto it = controls.begin(); it != controls.end();) {
            auto preIt = it++;
            preIt->second->OnKeyDown(keyCode);
        }
    }
    void Group::OnKeyUp(int keyCode) {
        for (auto it = controls.begin(); it != controls.end();) {
            auto preIt = it++;
            preIt->second->OnKeyUp(keyCode);
        }
    }
    void Group::OnMouseDown(int button, int mx, int my) {
        for (auto it = controls.begin(); it != controls.end();) {
            auto preIt = it++;
            preIt->second->OnMouseDown(button, mx, my);
        }
    }
    void Group::OnMouseUp(int button, int mx, int my) {
        for (auto it = controls.begin(); it != controls.end();) {
            auto preIt = it++;
            preIt->second->OnMouseUp(button, mx, my);
        }
    }
    void Group::OnMouseMove(int mx, int my) {
        for (auto it = controls.begin(); it != controls.end();) {
            auto preIt = it++;
            preIt->second->OnMouseMove(mx, my);
        }
    }
    void Group::OnMouseScroll(int mx, int my, int delta) {
        for (auto it = controls.begin(); it != controls.end();) {
            auto preIt = it++;
            preIt->second->OnMouseScroll(mx, my, delta);
        }
    }
    void Group::RemoveObject(std::list<std::pair<bool, IObject *>>::iterator it) {
        if (it->first) delete it->second;
        objects.erase(it);
    }
    void Group::RemoveObject3D(std::list<std::pair<bool, IObject3D *>>::iterator it) {
        if (it->first) delete it->second;
        object3ds.erase(it);
    }
    void Group::RemoveControl(std::list<std::pair<bool, IControl *>>::iterator it) {
        if (it->first) delete it->second;
        controls.erase(it);
    }
    void Group::RemoveControlObject(std::list<std::pair<bool, IControl *>>::iterator ctrlIt, std::list<std::pair<bool, IObject *>>::iterator objIt) {
        RemoveControl(ctrlIt);
        RemoveObject(objIt);
    }
    void Group::RemoveControlObject3D(std::list<std::pair<bool, IControl *>>::iterator ctrlIt, std::list<std::pair<bool, IObject3D *>>::iterator obj3dIt) {
        RemoveControl(ctrlIt);
        RemoveObject3D(obj3dIt);
    }
    void Group::AddNewObject(IObject *obj) {
        addObject(true, obj);
    }
    void Group::AddNewObject3D(IObject3D *obj3d) {
        addObject3D(true, obj3d);
    }
    void Group::InsertNewObject(IObject *obj, std::list<std::pair<bool, IObject *>>::iterator it) {
        insertObject(true, obj, it);
    }
    void Group::AddNewControl(IControl *ctrl) {
        addControl(true, ctrl);
    }
    void Group::AddNewControlObject(IControl *ctrl) {
        if (!dynamic_cast<IObject *>(ctrl))
            throw std::invalid_argument("The control must inherit both IObject and IControl.");
        addObject(false, dynamic_cast<IObject *>(ctrl));
        addControl(true, ctrl);
    }
    void Group::AddNewControlObject3D(IControl *ctrl) {
        if (!dynamic_cast<IObject3D *>(ctrl))
            throw std::invalid_argument("The control must inherit both IObject and IControl.");
        addObject3D(false, dynamic_cast<IObject3D *>(ctrl));
        addControl(true, ctrl);
    }
    void Group::AddRefObject(IObject &obj) {
        addObject(false, &obj);
    }
    void Group::AddRefObject3D(IObject3D &obj) {
        addObject3D(false, &obj);
    }
    void Group::InsertRefObject(IObject &obj, std::list<std::pair<bool, IObject *>>::iterator it) {
        insertObject(false, &obj, it);
    }
    void Group::AddRefControl(IControl &ctrl) {
        addControl(false, &ctrl);
    }
    void Group::AddRefControlObject(IControl &ctrl) {
        if (!dynamic_cast<IObject *>(&ctrl))
            throw std::invalid_argument("The control must inherit both IObject and IControl.");
        addObject(false, dynamic_cast<IObject *>(&ctrl));
        addControl(false, &ctrl);
    }
    void Group::AddRefControlObject3D(IControl &ctrl) {
        if (!dynamic_cast<IObject3D *>(&ctrl))
            throw std::invalid_argument("The control must inherit both IObject and IControl.");
        addObject3D(false, dynamic_cast<IObject3D *>(&ctrl));
        addControl(false, &ctrl);
    }
    std::list<IObject *> Group::GetObjects() {
        std::list<IObject *> list;
        for (auto &it : objects)
            list.push_back(it.second);
        return list;
    }
    std::list<IObject3D *> Group::GetObject3Ds() {
        std::list<IObject3D *> list;
        for (auto &it : object3ds)
            list.push_back(it.second);
        return list;
    }
    std::list<IControl *> Group::GetControls() {
        std::list<IControl *> list;
        for (auto &it : controls)
            list.push_back(it.second);
        return list;
    }
}
