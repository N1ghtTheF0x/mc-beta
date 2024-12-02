#ifndef __MINECRAFT_INTERFACES_IMESH_HPP
#define __MINECRAFT_INTERFACES_IMESH_HPP

#include <vector>

namespace Minecraft
{
    template<typename Vertex,typename Index>
    class IMesh
    {
    public:
        typedef std::vector<Vertex> Vertices;
        typedef std::vector<Index> Indices;

        virtual void addVertex(const Vertex& vertex) = 0;
        virtual void addVertex(Vertex&& vertex) = 0;
        virtual void addVertex(const Vertices& vertices) = 0;
        virtual void setVertex(size_t index,const Vertex& vertex) = 0;
        virtual void setVertex(size_t index,Vertex&& vertex) = 0;
        virtual Vertex& getVertex(size_t index) = 0;
        virtual const Vertex& getVertex(size_t index) const = 0;
        virtual Vertices& getVertices() = 0;
        virtual const Vertices& getVectices() const = 0;

        virtual void addIndex(const Index& index) = 0;
        virtual void addIndex(Index&& index) = 0;
        virtual void addIndex(const Indices& indices) = 0;
        virtual void setIndex(size_t index,const Index& idx) = 0;
        virtual void setIndex(size_t index,Index&& idx) = 0;
        virtual Index& getIndex(size_t index) = 0;
        virtual const Index& getIndex(size_t index) const = 0;
    };
}

#endif