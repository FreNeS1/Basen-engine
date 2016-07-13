#pragma once

#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <cassert>

namespace bas {

	template <typename Resource, typename Identifier>
	class ResourceHolder
	{
	public:
		template <typename Parameter>
		void				load(Identifier id, const std::string& filename, const Parameter& parameter);	// Loading a resource with a parameter
		void				load(Identifier id, const std::string& filename);								// Loading a resource by default
		Resource&			get(Identifier id);																// Returns a pointer to the resource
		const Resource&		get(Identifier id) const;														// (Const) Returns a pointer to the resource

	private:
		void				insertResource(Identifier id, std::unique_ptr<Resource> resource);	// internal way to insert in the map

	private:
		std::map<Identifier, std::unique_ptr<Resource>> resourceMap;
	};

#include "ResourceHolder.inl"	// We have to explicitly call the "source" file

}