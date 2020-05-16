#ifndef SRC_ECS_H_
#define SRC_ECS_H_

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
#include <assert.h>

class Component;
class Entity;
class Manager;

using ComponentID = std::size_t;
using Group = std::size_t;

inline ComponentID getUniqueID() {
	static ComponentID lastID = 0u;
	return lastID++;
}

//we want each component to have the same id no matter how many different components were created for different entities.
template <typename T>
inline ComponentID getComponentTypeID() noexcept {

	//we want to be able to check if the derived class is derived from the component base class,
	//only classes derived from the base class should get the componentTypeID
	static_assert(std::is_base_of<Component, T>::value,
			"T must inherit from the base component class!");

	static ComponentID typeID = getUniqueID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;
constexpr std::size_t maxGroups = 32;

using ComponentArray = std::array<Component*, maxComponents>;
using ComponentBitSet = std::bitset<maxComponents>;
using GroupBitSet = std::bitset<maxGroups>;


class Component{
public:
	Entity* entity;		//reference to the owner

	virtual void init() {}
	virtual void draw() {}
	virtual void update() {}

	virtual ~Component() {}
};


class Entity {

private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitset;
	GroupBitSet groupBitSet;

public:
	Entity(Manager& mManager) : manager(mManager) {}

	void update() {
		for(auto &c : components) c->update();
	}

	void draw() {
		for(auto &c : components) c->draw();
	}

	bool isActive() const{
		return active;
	}

	void destroy() {
		active = false;
	}

	bool hasGroup(Group mGroup) {
		return groupBitSet[mGroup];
	}

	void addGroup(Group mGroup);

	void delGroup(Group mGroup) {
		groupBitSet[mGroup] = false;
	}

	template <typename T>
	bool hasComponent() {
		return componentBitset[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs) {

//		checking if the entity already has the component
		assert(!hasComponent<T>());

		T* newComponent(new T(std::forward<TArgs>(mArgs)...));
		newComponent->entity = this;	//referencing to the component class's entity, i.e. defining the owner of the component
		std::unique_ptr<Component> uPtr{newComponent};

		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = newComponent;
		componentBitset[getComponentTypeID<T>()] = true;

		newComponent->init();
		return *newComponent;
	}

	template <typename T>
	T& getComponent() const {
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};


class Manager {

private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;

public:
	void update() {
		for(auto& e : entities) e->update();
	}

//	As we used the group rendering method to render different layers and directly
//	accessed the entity's draw method, this is not needed !! refer to Game.cpp file !!

//	void draw() {
//		for(auto& e : entities) e->draw();
//	}

	void refresh() {
		for(auto i{0u}; i < maxGroups; i++) {
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v),
					[i](Entity* mEntity){
						return !mEntity->isActive() || !mEntity->hasGroup(i);
					}),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
		[](const std::unique_ptr<Entity> &mEntity) {
			return !mEntity->isActive();
		}),
			std::end(entities));
	}

	void addToGroup(Entity* mEntity, Group mGroup) {
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup) {
		return groupedEntities[mGroup];
	}

	Entity& addEntity() {
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };
		entities.emplace_back(std::move(uPtr));
		return *e;
	}
};

#endif
