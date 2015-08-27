#ifndef INCLUDE_DOCUMENT_H
#define INCLUDE_DOCUMENT_H

#include "Entity.h"

class Document : public Entity {

	public:
		Document(const double x_, const double y_, const std::string& path_, const std::string& pathDocumentText_);
		virtual ~Document();

		virtual void update(const double dt_);
		virtual void render(const double cameraX_, const double cameraY_);

		void renderDocumentText();

		bool shouldRender;

	private:
		Sprite* documentText;

};

#endif //INCLUDE_DOCUMENT_H