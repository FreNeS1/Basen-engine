namespace bas {

	namespace Textures
	{
		enum ID			// This is a list of all the texture ID
		{
			Debug1,
			Debug2,
			Debug3,
			Debug4,
			Debug5
		};
	}

	namespace Fonts
	{
		enum ID			// This is a list of all the texture ID
		{
			Debug1,
			Debug2,
			Debug3,
			Debug4,
			Debug5
		};
	}
}

namespace sf
{
		class Texture;		// Foward declaration of sf::Texture
		class Font;
}

namespace bas {
	template <typename Resource, typename Identifier>
	class ResourceHolder;	// Foward declaration of a base ResourceHolder

	typedef ResourceHolder<sf::Texture, Textures::ID> TextureHolder;
	typedef ResourceHolder<sf::Font, Fonts::ID> FontHolder;
}
