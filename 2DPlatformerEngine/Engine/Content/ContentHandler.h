#ifndef CONTENT_CONTENT_HANDLER_H
#define CONTENT_CONTENT_HANDLER_H
#include "../Common.h"
#include "Texture2D.h"
#include "Shader.h"
#include <map>

namespace Content {

	class ContentHandler {
		SINGLETON(ContentHandler);

		string resourceFolder;

		std::map<string, Texture2D> loadedTextures;
		std::map<string, Shader> loadedShaders;

	public:

		void OnCreate();
		void OnDestroy();

		/// setter

		void SetResourceFolder(const string& resourceFolder_) {
			// make sure theres a slash
			resourceFolder = resourceFolder_ + "/";
		}

		/// loading content

		// unloads all managed content
		void UnloadContent();

		// loads files in resource folder and tracks files
		template<typename T>
		static T Load(const string& file);

		// loads files outside resource doler
		template<typename T>
		static T LoadUnmanaged(const string& file);

		// loads files outside resource folder and tracks files
		template<typename T>
		static T LoadManaged(const string& file);
	};

}

#endif // !CONTENT_CONTENT_HANDLER_H