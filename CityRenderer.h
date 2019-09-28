#pragma once

// renders map mesh, peds, cars and map objects
class CityRenderer final: public cxx::noncopyable
{
public:
    CityRenderer();

    bool Initialize();
    void Deinit();

    void RenderFrame();
    void InvalidateMapMesh();

private:
    // internals
    void BuildMapMesh();
    void CommitCityMeshData();

    void RenderFrameBegin();
    void RenderFrameEnd();

    void DrawCityMesh();
    void IssuePedsSprites();
    void IssueCarsSprites();
    void IssueMapObjectsSprites();
    void IssueProjectilesSprites();

    float ComputeDrawHeight(Pedestrian* pedestrian, const glm::vec3& position, float angleRadians);
    float ComputeDrawHeight(Vehicle* car, const glm::vec3& position, float angleRadians);

    // @param sprRotate: Angle in radians
    void DrawSprite(GpuTexture2D* texture, const TextureRegion& textureRegion, const glm::vec3& position, bool centerOrigin, float sprScale, float sprRotate);

    void SortDrawSpritesList();
    void GenerateDrawSpritesBatches();
    void RenderDrawSpritesBatches();

private:

    // drawing operation for single sprite
    struct DrawSpriteRec
    {
        glm::vec3 mPosition;
        glm::vec2 mSize;
        glm::vec2 mCenterOffset;
        glm::vec2 mTcUv0;
        glm::vec2 mTcUv1;
        float mRotate; // rotate in radians
        GpuTexture2D* mSpriteTexture;
    };

    // single batch of drawing sprites
    struct DrawSpriteBatch
    {
        unsigned int mFirstVertex;
        unsigned int mFirstIndex;
        unsigned int mVertexCount;
        unsigned int mIndexCount;
        GpuTexture2D* mSpriteTexture;
    };

    std::vector<SpriteVertex3D> mDrawSpritesVertices;
    std::vector<DrawIndex_t> mDrawSpritesIndices;

    std::vector<DrawSpriteRec> mDrawSpritesList;
    std::list<DrawSpriteBatch> mDrawSpritesBatchesList;

    StreamingVertexCache mSpritesVertexCache; 

    Rect2D mCityMapRectangle; // cached map area in tiles

    MapMeshData mCityMeshData[MAP_LAYERS_COUNT];
    GpuBuffer* mCityMeshBufferV;
    GpuBuffer* mCityMeshBufferI;
};