#include "GraphicEngine.h"

GraphicEngine::GraphicEngine()
{
}

bool GraphicEngine::init()
{
	static const D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE

	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	static const D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res=0;

	for(UINT driver_types_index=0; driver_types_index<num_driver_types;)
	{
		res=D3D11CreateDevice
		(
			NULL, 
			driver_types[driver_types_index],
			NULL, 
			NULL, 
			feature_levels, 
			num_feature_levels, 
			D3D11_SDK_VERSION, 
			&m_d3d_device, 
			&m_feature_level, 
			&m_imm_context
		);
		if(SUCCEEDED(res))
			break;

		++driver_types_index;
	}

	if (FAILED(res))
	{
		return false;
	}
	
	return true;
}

bool GraphicEngine::release()
{
	m_imm_context->Release();
	m_d3d_device->Release();
	return true;
}

GraphicEngine::~GraphicEngine()
{
}

GraphicEngine* GraphicEngine::get()
{
	static GraphicEngine engine;
	return &engine;
}
