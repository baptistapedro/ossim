//*******************************************************************
//
// License:  MIT
// 
// See LICENSE.txt file in the top level directory for more details.
// 
// Description:
//
// Contains class declaration for  ossimNormalizedU9RemapTable.  Table for
// normalizing unsigned 9 bit data.
//
//*******************************************************************
//  $Id$

#ifndef ossimNormalizedU9RemapTable_HEADER
#define ossimNormalizedU9RemapTable_HEADER

#include <ossim/imaging/ossimNormalizedRemapTable.h>
#include <ossim/base/ossimCommon.h> /* for round */

/**
 * @class ossimNormalizedU9RemapTable
 *
 * @brief Eleven bit normalized remap table to go to/from normalized value
 * to pixel value.
 */
class OSSIM_DLL ossimNormalizedU9RemapTable : public ossimNormalizedRemapTable
{
public:

   /** @brief default constructor */
   ossimNormalizedU9RemapTable();
   /** @brief virtual destructor */
   virtual ~ossimNormalizedU9RemapTable();


   enum
   {
      TABLE_ENTRIES = 512 //  2^9
   };

   /**
    * @brief Gets the number of table entries.
    * @return The number of entries in a table.
    */
   virtual ossim_int32 getEntries() const;

   /**
    *  @brief Gets a normalized value (between '0.0' and '1.0') from
    *  a pixel value.
    *
    *  @return Value between 0.0 and 1.0.
    */
   virtual ossim_float64 operator[](ossim_int32 pix) const;

   /**
    *  @brief Gets a normalized value (between '0.0' and '1.0') from
    *  a pixel value.
    *
    *  @return Value between 0.0 and 1.0.
    */
   virtual ossim_float64 normFromPix(ossim_int32 pix) const;

   /**
    * @brief Returns an pixel value as an int from a normalized value.
    *
    * @return Value between scalar range of remap table.
    */
   virtual ossim_int32 pixFromNorm(ossim_float64 normPix) const;   

private:

   static ossim_float64  theTable[TABLE_ENTRIES];
   static bool theTableIsInitialized;
   
};

inline ossim_int32 ossimNormalizedU9RemapTable::getEntries() const
{
   return TABLE_ENTRIES;
}

inline ossim_float64 ossimNormalizedU9RemapTable::operator[](
   ossim_int32 pix) const
{
   return ( (pix < TABLE_ENTRIES) ? (pix >= 0 ? theTable[pix] : 0.0) : 1.0);  
}

inline ossim_float64 ossimNormalizedU9RemapTable::normFromPix(
   ossim_int32 pix) const
{
   return ( (pix < TABLE_ENTRIES) ? (pix >= 0 ? theTable[pix] : 0.0) : 1.0);
}

inline ossim_int32 ossimNormalizedU9RemapTable::pixFromNorm(
   ossim_float64 normPix) const
{
   if(normPix <= 0.0) return 0;
   
   // un-normalize...
   ossim_float64 p = normPix * getNormalizer();

   // Ensure pixel is in range.
   p = ( (p < TABLE_ENTRIES) ? (p >= 0.0 ? p : 0.0) : getNormalizer());

   // Since going from double to int round...
   p = ossim::round<ossim_int32>(p);

   if(p == 0.0)
   {
      p = 1.0;
   }
   
   return static_cast<ossim_int32>(p);
}

#endif
