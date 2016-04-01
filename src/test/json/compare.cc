// Copyright (c) 2015 Dr. Colin Hirsch
// Please see LICENSE for license or visit https://github.com/taocpp/json/

#include "test.hh"

namespace tao
{
   namespace json
   {
      void test_lt( const value & a, const value & b )
      {
         TEST_ASSERT( ! ( a < a ) );
         TEST_ASSERT( ! ( b < b ) );
         TEST_ASSERT( ! ( a > a ) );
         TEST_ASSERT( ! ( b > b ) );
         TEST_ASSERT( a < b );
         TEST_ASSERT( b > a );
         TEST_ASSERT( ! ( a > b ) );
         TEST_ASSERT( ! ( b < a ) );

         TEST_ASSERT( a == a );
         TEST_ASSERT( b == b );
         TEST_ASSERT( ! ( a != a ) );
         TEST_ASSERT( ! ( b != b ) );
         TEST_ASSERT( a != b );
         TEST_ASSERT( b != a );
         TEST_ASSERT( ! ( a == b ) );
         TEST_ASSERT( ! ( b == a ) );

         TEST_ASSERT( a <= a );
         TEST_ASSERT( b <= b );
         TEST_ASSERT( a >= a );
         TEST_ASSERT( b >= b );
         TEST_ASSERT( a <= b );
         TEST_ASSERT( b >= a );
         TEST_ASSERT( ! ( a >= b ) );
         TEST_ASSERT( ! ( b <= a ) );
      }

      void test_null()
      {
         const value a;
         const value b( nullptr );

         TEST_ASSERT( a.type() == type::NULL_ );
         TEST_ASSERT( b.type() == type::NULL_ );

         TEST_ASSERT( a == b );
      }

      void test_bool()
      {
         const value t( true );
         const value f( false );

         TEST_ASSERT( t.type() == type::BOOL_ );
         TEST_ASSERT( f.type() == type::BOOL_ );

         test_lt( f, t );
      }

      template< typename N >
      void test_number()
      {
         const value a( N( 42 ) );
         const value b( N( 43 ) );

         test_lt( a, b );
      }

      void test_string()
      {
         const value a( "bar" );
         const value b( "foo" );

         TEST_ASSERT( a.type() == type::STRING );
         TEST_ASSERT( b.type() == type::STRING );

         test_lt( a, b );
      }

      void test_array()
      {
         const value a = from_string( "[ 1, 2 ]" );
         const value b = from_string( "[ 1, 3 ]" );
         const value c = from_string( "[ 2, 1 ]" );

         TEST_ASSERT( a.type() == type::ARRAY );
         TEST_ASSERT( b.type() == type::ARRAY );
         TEST_ASSERT( c.type() == type::ARRAY );

         test_lt( a, b );
         test_lt( a, c );
         test_lt( b, c );
      }

      void test_object()
      {
         const value a = from_string( "{ \"a\" : null }" );
         const value b = from_string( "{ \"a\" : true }" );
         const value c = from_string( "{ \"c\" : null }" );
         const value d = from_string( "{ \"d\" : 1, \"e\" : 2 }" );
         const value e = from_string( "{ \"d\" : 1, \"e\" : 3 }" );
         const value f = from_string( "{ \"d\" : 2, \"e\" : 3 }" );
         const value g = from_string( "{ \"z\" : 2, \"e\" : 3 }" );

         TEST_ASSERT( a.type() == type::OBJECT );
         TEST_ASSERT( b.type() == type::OBJECT );
         TEST_ASSERT( c.type() == type::OBJECT );
         TEST_ASSERT( d.type() == type::OBJECT );
         TEST_ASSERT( e.type() == type::OBJECT );
         TEST_ASSERT( f.type() == type::OBJECT );
         TEST_ASSERT( g.type() == type::OBJECT );

         test_lt( a, b );
         test_lt( a, c );
         test_lt( a, d );
         test_lt( a, e );
         test_lt( a, f );
         test_lt( a, g );
         test_lt( b, c );
         test_lt( b, d );
         test_lt( b, e );
         test_lt( b, f );
         test_lt( b, g );
         test_lt( c, d );
         test_lt( c, e );
         test_lt( c, f );
         test_lt( c, g );
         test_lt( d, e );
         test_lt( d, f );
         test_lt( d, g );
         test_lt( e, f );
         test_lt( e, g );
         test_lt( f, g );
      }

      void test_mixed()
      {
         const value a;
         const value b = from_string( "true" );
         const value c = from_string( "42" );
         const value d = from_string( "43.0" );
         const value e = from_string( "\"string\"" );
         const value f = from_string( "[]" );
         const value g = from_string( "{}" );

         TEST_ASSERT( a.type() == type::NULL_ );
         TEST_ASSERT( b.type() == type::BOOL_ );
         TEST_ASSERT( c.type() == type::INT64 );
         TEST_ASSERT( d.type() == type::DOUBLE );
         TEST_ASSERT( e.type() == type::STRING );
         TEST_ASSERT( f.type() == type::ARRAY );
         TEST_ASSERT( g.type() == type::OBJECT );

         test_lt( a, b );
         test_lt( a, c );
         test_lt( a, d );
         test_lt( a, e );
         test_lt( a, f );
         test_lt( a, g );
         test_lt( b, c );
         test_lt( b, d );
         test_lt( b, e );
         test_lt( b, f );
         test_lt( b, g );
         test_lt( c, d );
         test_lt( c, e );
         test_lt( c, f );
         test_lt( c, g );
         test_lt( d, e );
         test_lt( d, f );
         test_lt( d, g );
         test_lt( e, f );
         test_lt( e, g );
         test_lt( f, g );
      }

      void unit_test()
      {
         test_null();
         test_bool();
         test_number< signed char >();
         test_number< unsigned char >();
         test_number< signed short >();
         test_number< unsigned short >();
         test_number< signed int >();
         test_number< unsigned int >();
         test_number< signed long >();
         test_number< signed long long >();
         test_number< int64_t >();
         test_number< double >();
         test_string();
         test_array();
         test_object();
         test_mixed();
      }

   } // json

} // tao

#include "main.hh"