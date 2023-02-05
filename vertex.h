#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <fstream>

class Vertex {
   //! Overloaded ostream operator which writes all vertex data on an open textfile stream

    friend std::ostream& operator<< (std::ostream&, const Vertex&);

   //! Overloaded ostream operator which reads all vertex data from an open textfile stream
   friend std::istream& operator>> (std::istream&, Vertex&);

private:
   float m_xyz[3];       	// position i 3D
   float m_normal[3];    // normal in 3D or rgb colors
   float m_st[2];        	// texture coordinates if used

public:
   Vertex();
  Vertex(float x, float y, float z, float r, float g, float b);
  inline float& operator[](size_t index) {
      if(index >= 8) throw std::range_error("Index " + std::to_string(index) + " for vertex.");

      if(index < 3) {
          return m_xyz[index];
      } else if(index < 6) {
          return m_normal[index-3];
      }
      else {
          return m_st[index-6];
      }
  }

};
#endif // VERTEX_H
