//----------------------------------*-C++-*----------------------------------//
/*!
 * \file   meshReaders/Mesh_Reader.hh
 * \author John McGhee
 * \date   Fri Feb 25 08:14:54 2000
 * \brief  Header file for the RTT Mesh_Reader base class.
 * \note   Copyright (C) 2016-2017 Los Alamos National Security, LLC.
 *         All rights reserved.
 */
//---------------------------------------------------------------------------//
// $Id$
//---------------------------------------------------------------------------//

#ifndef __meshReaders_Mesh_Reader_hh__
#define __meshReaders_Mesh_Reader_hh__

#include "ds++/SP.hh"
#include "mesh_element/Element_Definition.hh"
#include <map>
#include <set>

namespace rtt_meshReaders {

//===========================================================================//
/*!
 * \class Mesh_Reader
 * \brief Base class for the RTT mesh readers. 
 *
 * This class provides the template from which all other
 * mesh readers inherit. It provides a standard intefrace
 * to mesh information for all clients. The interface
 * supports structured and unstructured meshes. Both
 * so called "AMR" or "hanging-node" meshes and C0 connectivity
 * meshes can be described.
 */
// revision history:
// -----------------
// 0) original
//
//===========================================================================//

class DLL_PUBLIC_meshReaders Mesh_Reader {
  // NESTED CLASSES AND TYPEDEFS

  // DATA

public:
  // CREATORS

  //Defaulted: Mesh_Reader();
  //Defaulted: Mesh_Reader(const Mesh_Reader &rhs);

  virtual ~Mesh_Reader() {
    //Empty
  }

  // MANIPULATORS

  //Defaulted: Mesh_Reader& operator=(const Mesh_Reader &rhs);

  // ACCESSORS

  /*!
     * \brief Provides node coordinates for all the nodes in the
     * mesh.
     *
     * Not all the nodes returned herein have to be used to define 
     * a mesh element. For example some nodes may be children, dudded,
     * or tracer nodes. The operator [i][j] returns
     * node i, coordinate j.
     *
     */
  virtual std::vector<std::vector<double>> get_node_coords() const = 0;

  /*!
     * \brief Provides the units (inches, feet, cm, meters, etc.) of the
     *        node coordinates. 
     */
  virtual std::string get_node_coord_units() const = 0;

  /*!
     * \brief Returns node numbers of the mesh elements.
     *
     * Node numbers are 0 based and refer to the nodes 
     * returned by the Mesh_Reader.get_node_coords() method. This
     * information determines the connectivity of the mesh. It
     * uniquely defines all the elements in the mesh, and their
     * relationship to each other. Any mix of element types is
     * allowed including multple dimensions. The elements
     * may be spatially disjoint. The operator [i][j] returns
     * cell i, node j.
     *
     */
  virtual std::vector<std::vector<int>> get_element_nodes() const = 0;

  /*!
     * \brief Returns the type of all the elements in the mesh. 
     *
     */
  virtual std::vector<rtt_mesh_element::Element_Definition::Element_Type>
  get_element_types() const = 0;

  /*!
     * \brief Returns the unique element types that are defined in the mesh.
     *
     */
  virtual std::vector<rtt_mesh_element::Element_Definition::Element_Type>
  get_unique_element_types() const = 0;

  /*!
     * \brief Returns node sub-sets.
     *
     * Returned node numbers are 0 based and refer to the nodes 
     * returned by the Mesh_Reader.get_node_coords() method.
     * This method provides a capability to flag certain sub-sets of the
     * nodes returned by the Mesh_Reader.get_node_coords() method. This
     * can be useful for flagging certain nodes or sets of nodes for
     * some special treatement such as edits or sources. The string
     * key to the map provides a unique and hopefully descriptive name
     * for each node sub-set.
     */
  virtual std::map<std::string, std::set<int>> get_node_sets() const = 0;

  /*!
     * \brief Returns element sub-sets.
     *
     * Returned element numbers are 0 based and refer to the elements
     * returned by the Mesh_Reader.get_element_nodes() method.
     * This method provides a capability to flag certain sub-sets of the
     * elements returned by the Mesh_Reader.get_element_nodes() method. This
     * can be useful for flagging certain elements or sets of elements for
     * some special treatement such as edits, sources, material assignments,
     * boudndary conditions, etc. The string
     * key to the map provides a unique and hopefully descriptive name
     * for each element sub-set.
     */
  virtual std::map<std::string, std::set<int>> get_element_sets() const = 0;

  //! Returns the title of the mesh.
  virtual std::string get_title() const = 0;

  virtual std::vector<rtt_dsxx::SP<rtt_mesh_element::Element_Definition>>
  get_element_defs() const {
    return std::vector<rtt_dsxx::SP<rtt_mesh_element::Element_Definition>>();
  };

  //! Provides a check on the integrity of the mesh data.
  virtual bool invariant() const = 0;

  virtual size_t get_dims_ndim() const = 0;

private:
  // IMPLEMENTATION
};

} // end namespace rtt_meshReaders

#endif // __meshReaders_Mesh_Reader_hh__

//---------------------------------------------------------------------------//
// end of meshReaders/Mesh_Reader.hh
//---------------------------------------------------------------------------//
