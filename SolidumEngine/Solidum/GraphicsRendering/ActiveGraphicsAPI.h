#pragma once

enum SUPPORTED_GRAPHICS_API {
	DIRECTX11,
	UNKNOWN
};

class ActiveGraphicsAPI {
private:
	static SUPPORTED_GRAPHICS_API _currentAPI;
public:

	static void setCurrentAPI(SUPPORTED_GRAPHICS_API api) {
		_currentAPI = api;
	}

	static SUPPORTED_GRAPHICS_API getCurrentAPI() {
		return _currentAPI;
	}
};

