/*
  Copyright (c) 2013 Matthew Stump

  This file is part of libprz.

  libprz is free software: you can redistribute it and/or modify
  it under the terms of the GNU Affero General Public License as
  published by the Free Software Foundation, either version 3 of the
  License, or (at your option) any later version.

  libprz is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Affero General Public License for more details.

  You should have received a copy of the GNU Affero General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __X_INDEX_SLICE_HPP_INCLUDED__
#define __X_INDEX_SLICE_HPP_INCLUDED__

#include <vector>
#include <boost/noncopyable.hpp>
#include <boost/ptr_container/ptr_list.hpp>

#include "base_types.hpp"
#include "status.hpp"

namespace prz {

    class index_reader_t;
    class index_writer_t;

    class index_slice_t
        : boost::noncopyable
    {
    public:

        struct index_node_t {
            index_address_t offset;
            index_segment_t segment;

            index_node_t(const index_node_t& node);

            index_node_t(index_address_t offset);

            index_node_t(index_address_t         offset,
                         const index_segment_ptr data);

            void
            zero();
        };

        typedef boost::ptr_list<index_node_t> index_container;
        typedef index_container::iterator iterator;

        index_slice_t(index_partition_t partition,
                const char*       field,
                size_t            field_size,
                index_address_t   value);

        index_slice_t(index_partition_t partition,
                const byte_t*     field,
                size_t            field_size,
                index_address_t   value);

        inline iterator
        begin()
        {
            return _index.begin();
        }

        inline iterator
        end()
        {
            return _index.end();
        }

        inline iterator
        insert(iterator      pos,
               index_node_t* value)
        {
            return _index.insert(pos, value);
        }

        inline void
        clear()
        {
            _index.clear();
        }

        inline void
        erase(iterator first,
              iterator last)
        {
            _index.erase(first, last);
        }

        inline void
        erase(iterator position)
        {
            _index.erase(position);
        }

        inline size_t
        size()
        {
            return _index.size();
        }

        static prz::status_t
        execute(index_operation_enum operation,
                index_slice_t&             a_index,
                index_slice_t&             b_index,
                index_slice_t&             output);

        prz::status_t
        execute(prz::index_operation_enum operation,
                prz::index_reader_t*      reader,
                index_partition_t         partition,
                const byte_t*             field,
                size_t                    field_size,
                index_address_t           value,
                index_slice_t&            output);

        prz::status_t
        execute(prz::index_operation_enum operation,
                prz::index_reader_t*      reader,
                index_partition_t         partition,
                const byte_t*             field,
                size_t                    field_size,
                index_address_t           value);

        prz::status_t
        bit(prz::index_reader_t* reader,
            prz::index_writer_t* writer,
            index_address_t      bit,
            bool                 state);

        bool
        bit(index_address_t      bit);

        index_partition_t
        partition() const;

        const byte_t*
        field() const;

        size_t
        field_size() const;

        index_address_t
        value() const;


    private:
        index_container     _index;
        index_partition_t   _partition;
        std::vector<byte_t> _field;
        index_address_t     _value;
    };

} // namespace prz


#endif // __X_INDEX_SLICE_HPP_INCLUDED__
