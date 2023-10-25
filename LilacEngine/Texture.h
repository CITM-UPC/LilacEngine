#pragma once
#include "Module.h"
#include "Globals.h"

class Texture
{
private:
	uint _id;

public:
	typedef std::shared_ptr<Texture> Ptr;
	explicit Texture(const std::string& path);
	Texture(Texture&& tex) noexcept;
	void bind() const;
	~Texture();

private:
	Texture(const Texture&);
	Texture operator=(const Texture&);

};

