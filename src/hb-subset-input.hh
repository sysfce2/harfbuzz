/*
 * Copyright © 2018  Google, Inc.
 *
 *  This is part of HarfBuzz, a text shaping library.
 *
 * Permission is hereby granted, without written agreement and without
 * license or royalty fees, to use, copy, modify, and distribute this
 * software and its documentation for any purpose, provided that the
 * above copyright notice and the following two paragraphs appear in
 * all copies of this software.
 *
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE TO ANY PARTY FOR
 * DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES
 * ARISING OUT OF THE USE OF THIS SOFTWARE AND ITS DOCUMENTATION, EVEN
 * IF THE COPYRIGHT HOLDER HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE COPYRIGHT HOLDER SPECIFICALLY DISCLAIMS ANY WARRANTIES, INCLUDING,
 * BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND
 * FITNESS FOR A PARTICULAR PURPOSE.  THE SOFTWARE PROVIDED HEREUNDER IS
 * ON AN "AS IS" BASIS, AND THE COPYRIGHT HOLDER HAS NO OBLIGATION TO
 * PROVIDE MAINTENANCE, SUPPORT, UPDATES, ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Google Author(s): Garret Rieger, Roderick Sheeter
 */

#ifndef HB_SUBSET_INPUT_HH
#define HB_SUBSET_INPUT_HH


#include "hb.hh"

#include "hb-subset.h"
#include "hb-map.hh"
#include "hb-set.hh"

#include "hb-font.hh"

HB_MARK_AS_FLAG_T (hb_subset_flags_t);

struct hb_subset_input_t
{
  hb_object_header_t header;

  union {
    struct {
      hb_set_t *glyphs;
      hb_set_t *unicodes;
      hb_set_t *no_subset_tables;
      hb_set_t *drop_tables;
      hb_set_t *name_ids;
      hb_set_t *name_languages;
      hb_set_t *layout_features;
    } sets;
    hb_set_t* set_ptrs[sizeof (sets) / sizeof (hb_set_t*)];
  };

  unsigned flags;

  inline unsigned num_sets () const
  {
    return sizeof (set_ptrs) / sizeof (hb_set_t*);
  }

  inline hb_array_t<hb_set_t*> sets_iter ()
  {
    return hb_array_t<hb_set_t*> (set_ptrs, num_sets ());
  }

  inline hb_set_t* unicodes()
  {
    return sets.unicodes;
  }

  inline const hb_set_t* unicodes() const
  {
    return sets.unicodes;
  }

  inline hb_set_t* glyphs ()
  {
    return sets.glyphs;
  }

  inline const hb_set_t* glyphs () const
  {
    return sets.glyphs;
  }

  inline hb_set_t* name_ids ()
  {
    return sets.name_ids;
  }

  inline const hb_set_t* name_ids () const
  {
    return sets.name_ids;
  }

  inline hb_set_t* name_languages ()
  {
    return sets.name_languages;
  }

  inline const hb_set_t* name_languages () const
  {
    return sets.name_languages;
  }

  inline hb_set_t* no_subset_tables ()
  {
    return sets.no_subset_tables;
  }

  inline const hb_set_t* no_subset_tables () const
  {
    return sets.no_subset_tables;
  }

  inline hb_set_t* drop_tables ()
  {
    return sets.drop_tables;
  }

  inline const hb_set_t* drop_tables () const
  {
    return sets.drop_tables;
  }

  inline hb_set_t* layout_features ()
  {
    return sets.layout_features;
  }

  inline const hb_set_t* layout_features () const
  {
    return sets.layout_features;
  }

  bool in_error () const
  {
    for (unsigned i = 0; i < num_sets (); i++)
    {
      if (unlikely (set_ptrs[i]->in_error ()))
        return true;
    }
    return false;
  }
};


#endif /* HB_SUBSET_INPUT_HH */
