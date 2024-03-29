#pragma once
#include <BaseInclude.h>
#include <memory>

#include STRING_INCLUDE_PATH

namespace Core
{
	enum AssetType
	{
		//	Raw assets
		AssetType_Invalid = -1,
		AssetType_RawTexture,
		AssetType_RawShader,
		AssetType_RawFBX,
		//	Generated assets by engine
		AssetType_Texture,
		AssetType_Shader,
		AssetType_Material,
		AssetType_StaticMesh,
		AssetType_DynamicMesh,
		AssetType_Entity,
		AssetType_World,
		AssetType_Count,
	};

	//	Assets not only at runtime,
//	can be serialized and deserialized.
	class IAsset
	{
	public:
		ctd::string name;

		IAsset() {};
		virtual void OnPause() = 0;
		virtual void OnResume() = 0;
		virtual ~IAsset() {};
	};

	//	Raw assets, e.g. .fbx, .png and so on that generated by DCCs,
	//	can be read only.
	class IRawAsset
	{
	private:
		//	TODO:
		//			暂时没想好raw资源更新后去更新runtime资源的机制,
		//			所以这个变量目前没有设置
		std::weak_ptr<IAsset> m_pRuntimeAsset;
	protected:
		Bool m_beingUsed;

	public:
		ctd::string fullPathName;
		ctd::string fileName;
		ctd::string fileNameWithExt;		//	文件名,含扩展名
		AssetType type;

		IRawAsset() : m_beingUsed(False) {}
		virtual void BeginUse() = 0;
		virtual void Reload() = 0;
		virtual ~IRawAsset() {}
	};
}