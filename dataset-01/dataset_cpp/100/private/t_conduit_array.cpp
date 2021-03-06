// Copyright (c) Lawrence Livermore National Security, LLC and other Conduit
// Project developers. See top-level LICENSE AND COPYRIGHT files for dates and
// other details. No copyright assignment is required to contribute to Conduit.

//-----------------------------------------------------------------------------
///
/// file: conduit_array.cpp
///
//-----------------------------------------------------------------------------

#include "conduit.hpp"

#include <iostream>
#include "gtest/gtest.h"

using namespace conduit;

//-----------------------------------------------------------------------------
TEST(conduit_array, basic_construction)
{
    std::vector<int8> data1(10,8);
    std::vector<int8> data2(10,-8);

    void *data1_ptr = &data1[0];
    const void *cdata2_ptr = &data2[0];

    DataArray<int8> da_1(data1_ptr,DataType::int8(10));

    std::cout << da_1.to_string() << std::endl;

    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(8,da_1[i]);
    }

    DataArray<int8> da_2(cdata2_ptr,DataType::int8(10));

    std::cout << da_2.to_string() << std::endl;

    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(-8,da_2[i]);
    }

    DataArray<int8> da_3(da_1);
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(8,da_3[i]);
    }

    da_3[0] = 16;

    da_3 = da_2;

    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(-8,da_2[i]);
    }

    da_3[0] = -16;

    std::cout << da_3.to_string() << std::endl;
    
    // test other variants of to_string and to stream, etc
    da_3.to_string_stream(std::cout);
    da_3.to_json_stream(std::cout);

    EXPECT_EQ(16,data1[0]);
    EXPECT_EQ(-16,data2[0]);
}

//-----------------------------------------------------------------------------
TEST(conduit_array, array_stride_int8)
{
    std::vector<int8> data(20,0);

    for(int i=0;i<20;i+=2)
    {
        data[i] = i/2;
    }

    for(int i=1;i<20;i+=2)
    {
        data[i] = -i/2;
    }
    std::cout << "Full Data" << std::endl;

    for(int i=0;i<20;i++)
    {
        std::cout << (int64) data[i] << " ";
    }
    std::cout << std::endl;
 
    DataType arr_t(DataType::INT8_ID,
                   10,
                   0,
                   sizeof(int8)*2, // stride
                   sizeof(int8),
                   Endianness::DEFAULT_ID);
    Node n;
    n["value"].set_external(arr_t,&data[0]);


    int8_array arr = n["value"].as_int8_array();

    for(int i=0;i<10;i++)
    {
        // note: the cast is for proper printing to std::out
        std::cout << "value[" << i << "] = " << ((int64)arr[i] ) << std::endl;
    }
    std::cout << std::endl;

    EXPECT_EQ(arr[5],5);
    EXPECT_EQ(arr[9],9);

    arr[1] = 100;
    EXPECT_EQ(data[2],100);
    
        std::cout << "Full Data" << std::endl;

    for(int i=0;i<20;i++)
    {
        std::cout << (int64) data[i] << " ";
    }
    std::cout << std::endl;


    Node n2(DataType::int8(10,sizeof(int8),sizeof(int8)*2),
            &data[0],
            true); /// true for external

    int8_array arr_2 = n2.as_int8_array();
    
    for(int i=0;i<10;i++)
    {
        // note: the cast is for proper printing to std::out
        std::cout << "value[" << i << "] = " <<  ((int64)arr_2[i] ) << std::endl;
    }
    std::cout << std::endl;
    
    EXPECT_EQ(arr_2[0],0);
    EXPECT_EQ(arr_2[9],-9);   

}    

//-----------------------------------------------------------------------------
TEST(conduit_array, array_stride_int8_external)
{
    std::vector<int64> data(20,0);

    for(int i=0;i<20;i+=2)
    {
        data[i] = i/2;
    }

    for(int i=1;i<20;i+=2)
    {
        data[i] = -i/2;
    }
    std::cout << "Full Data" << std::endl;

    for(int i=0;i<20;i++)
    {
        std::cout << (int64) data[i] << " ";
    }
    std::cout << std::endl;
 
    Node n;
    n["value"].set_external(data);

    int64_array arr = n["value"].as_int64_array();

    for(int i=0;i<20;i++)
    {
        // note: the cast is for proper printing to std::out
        std::cout << "value[" << i << "] = " << arr[i] << std::endl;
    }
    std::cout << std::endl;

    data[2]*=10;
    data[3]*=10;

    EXPECT_EQ(arr[2],10);
    EXPECT_EQ(arr[3],-10);

}


//-----------------------------------------------------------------------------
TEST(conduit_array, set_using_ptrs)
{
    //in this case we are  using std vectors to init data conveniently
    // we are actually testing the pointer set cases
    // we test std vector set cases directly in "set_using_std_vectors"
    std::vector<int8>  v_int8(10,-8);
    std::vector<int16> v_int16(10,-16);
    std::vector<int32> v_int32(10,-32);
    std::vector<int64> v_int64(10,-64);

    std::vector<uint8>  v_uint8(10,8);
    std::vector<uint16> v_uint16(10,16);
    std::vector<uint32> v_uint32(10,32);
    std::vector<uint64> v_uint64(10,64);

    std::vector<float32> v_float32(10,32.0);
    std::vector<float64> v_float64(10,64.0);



    Node n;
    
    // int8_array
    n["vint8"].set(DataType::int8(10));
    n["vint8"].as_int8_array().set(&v_int8[0],10);
    int8 *n_int8_ptr = n["vint8"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int8_ptr[i],v_int8[i]);
    }

    // int16_array
    n["vint16"].set(DataType::int16(10));
    n["vint16"].as_int16_array().set(&v_int16[0],10);
    int16 *n_int16_ptr = n["vint16"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int16_ptr[i],v_int16[i]);
    }

    // int32_array
    n["vint32"].set(DataType::int32(10));
    n["vint32"].as_int32_array().set(&v_int32[0],10);
    int32 *n_int32_ptr = n["vint32"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int32_ptr[i],v_int32[i]);
    }

    // int64_array
    n["vint64"].set(DataType::int64(10));
    n["vint64"].as_int64_array().set(&v_int64[0],10);
    int64 *n_int64_ptr = n["vint64"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int64_ptr[i],v_int64[i]);
    }

    // uint8_array
    n["vuint8"].set(DataType::uint8(10));
    n["vuint8"].as_uint8_array().set(&v_uint8[0],10);
    uint8 *n_uint8_ptr = n["vuint8"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint8_ptr[i],v_uint8[i]);
    }

    // uint16_array
    n["vuint16"].set(DataType::uint16(10));
    n["vuint16"].as_uint16_array().set(&v_uint16[0],10);
    uint16 *n_uint16_ptr = n["vuint16"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint16_ptr[i],v_uint16[i]);
    }

    // uint32_array
    n["vuint32"].set(DataType::uint32(10));
    n["vuint32"].as_uint32_array().set(&v_uint32[0],10);
    uint32 *n_uint32_ptr = n["vuint32"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint32_ptr[i],v_uint32[i]);
    }

    // uint64_array
    n["vuint64"].set(DataType::uint64(10));
    n["vuint64"].as_uint64_array().set(&v_uint64[0],10);
    uint64 *n_uint64_ptr = n["vuint64"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint64_ptr[i],v_uint64[i]);
    }


    // float32_array
    n["vfloat32"].set(DataType::float32(10));
    n["vfloat32"].as_float32_array().set(&v_float32[0],10);
    float32 *n_float32_ptr = n["vfloat32"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float32_ptr[i],v_float32[i]);
    }

    // float64_array
    n["vfloat64"].set(DataType::float64(10));
    n["vfloat64"].as_float64_array().set(&v_float64[0],10);
    float64 *n_float64_ptr = n["vfloat64"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float64_ptr[i],v_float64[i]);
    }

}


//-----------------------------------------------------------------------------
TEST(conduit_array, set_using_data_array)
{
    std::vector<int8>  v_int8(10,-8);
    std::vector<int16> v_int16(10,-16);
    std::vector<int32> v_int32(10,-32);
    std::vector<int64> v_int64(10,-64);

    std::vector<uint8>  v_uint8(10,8);
    std::vector<uint16> v_uint16(10,16);
    std::vector<uint32> v_uint32(10,32);
    std::vector<uint64> v_uint64(10,64);

    std::vector<float32>  v_float32(10,32.0);
    std::vector<float64>  v_float64(10,64.0);

    int8_array    va_int8(&v_int8[0],DataType::int8(10));
    int16_array   va_int16(&v_int16[0],DataType::int16(10));
    int32_array   va_int32(&v_int32[0],DataType::int32(10));
    int64_array   va_int64(&v_int64[0],DataType::int64(10));

    uint8_array   va_uint8(&v_uint8[0],DataType::uint8(10));
    uint16_array  va_uint16(&v_uint16[0],DataType::uint16(10));
    uint32_array  va_uint32(&v_uint32[0],DataType::uint32(10));
    uint64_array  va_uint64(&v_uint64[0],DataType::uint64(10));

    float32_array  va_float32(&v_float32[0],DataType::float32(10));
    float64_array  va_float64(&v_float64[0],DataType::float64(10));


    Node n;
    
    // int8_array
    n["vint8"].set(DataType::int8(10));
    n["vint8"].as_int8_array().set(va_int8);
    int8 *n_int8_ptr = n["vint8"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int8_ptr[i],va_int8[i]);
    }

    // int16_array
    n["vint16"].set(DataType::int16(10));
    n["vint16"].as_int16_array().set(va_int16);
    int16 *n_int16_ptr = n["vint16"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int16_ptr[i],va_int16[i]);
    }

    // int32_array
    n["vint32"].set(DataType::int32(10));
    n["vint32"].as_int32_array().set(va_int32);
    int32 *n_int32_ptr = n["vint32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int32_ptr[i],va_int32[i]);
    }

    // int64_array
    n["vint64"].set(DataType::int64(10));
    n["vint64"].as_int64_array().set(va_int64);
    int64 *n_int64_ptr = n["vint64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int64_ptr[i],va_int64[i]);
    }

    // uint8_array
    n["vuint8"].set(DataType::uint8(10));
    n["vuint8"].as_uint8_array().set(va_uint8);
    uint8 *n_uint8_ptr = n["vuint8"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint8_ptr[i],va_uint8[i]);
    }

    // uint16_array
    n["vuint16"].set(DataType::uint16(10));
    n["vuint16"].as_uint16_array().set(va_uint16);
    uint16 *n_uint16_ptr = n["vuint16"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint16_ptr[i],va_uint16[i]);
    }

    // uint32_array
    n["vuint32"].set(DataType::uint32(10));
    n["vuint32"].as_uint32_array().set(va_uint32);
    uint32 *n_uint32_ptr = n["vuint32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint32_ptr[i],va_uint32[i]);
    }

    // uint64_array
    n["vuint64"].set(DataType::uint64(10));
    n["vuint64"].as_uint64_array().set(va_uint64);
    uint64 *n_uint64_ptr = n["vuint64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint64_ptr[i],va_uint64[i]);
    }


    // float32_array
    n["vfloat32"].set(DataType::float32(10));
    n["vfloat32"].as_float32_array().set(va_float32);
    float32 *n_float32_ptr = n["vfloat32"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float32_ptr[i],va_float32[i]);
    }

    // float64_array
    n["vfloat64"].set(DataType::float64(10));
    n["vfloat64"].as_float64_array().set(va_float64);
    float64 *n_float64_ptr = n["vfloat64"].value();
    for(index_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float64_ptr[i],va_float64[i]);
    }

}



//-----------------------------------------------------------------------------
TEST(conduit_array, set_using_std_vectors)
{
    std::vector<int8>  v_int8(10,-8);
    std::vector<int16> v_int16(10,-16);
    std::vector<int32> v_int32(10,-32);
    std::vector<int64> v_int64(10,-64);

    std::vector<uint8>  v_uint8(10,8);
    std::vector<uint16> v_uint16(10,16);
    std::vector<uint32> v_uint32(10,32);
    std::vector<uint64> v_uint64(10,64);

    std::vector<float32>  v_float32(10,32.0);
    std::vector<float64>  v_float64(10,64.0);


    Node n;
    
    // int8_array
    n["vint8"].set(DataType::int8(10));
    n["vint8"].as_int8_array().set(v_int8);
    int8 *n_int8_ptr = n["vint8"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int8_ptr[i],v_int8[i]);
    }

    // int16_array
    n["vint16"].set(DataType::int16(10));
    n["vint16"].as_int16_array().set(v_int16);
    int16 *n_int16_ptr = n["vint16"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int16_ptr[i],v_int16[i]);
    }

    // int32_array
    n["vint32"].set(DataType::int32(10));
    n["vint32"].as_int32_array().set(v_int32);
    int32 *n_int32_ptr = n["vint32"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int32_ptr[i],v_int32[i]);
    }

    // int64_array
    n["vint64"].set(DataType::int64(10));
    n["vint64"].as_int64_array().set(v_int64);
    int64 *n_int64_ptr = n["vint64"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_int64_ptr[i],v_int64[i]);
    }

    // uint8_array
    n["vuint8"].set(DataType::uint8(10));
    n["vuint8"].as_uint8_array().set(v_uint8);
    uint8 *n_uint8_ptr = n["vuint8"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint8_ptr[i],v_uint8[i]);
    }

    // uint16_array
    n["vuint16"].set(DataType::uint16(10));
    n["vuint16"].as_uint16_array().set(v_uint16);
    uint16 *n_uint16_ptr = n["vuint16"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint16_ptr[i],v_uint16[i]);
    }

    // uint32_array
    n["vuint32"].set(DataType::uint32(10));
    n["vuint32"].as_uint32_array().set(v_uint32);
    uint32 *n_uint32_ptr = n["vuint32"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint32_ptr[i],v_uint32[i]);
    }

    // uint64_array
    n["vuint64"].set(DataType::uint64(10));
    n["vuint64"].as_uint64_array().set(v_uint64);
    uint64 *n_uint64_ptr = n["vuint64"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_uint64_ptr[i],v_uint64[i]);
    }


    // float32_array
    n["vfloat32"].set(DataType::float32(10));
    n["vfloat32"].as_float32_array().set(v_float32);
    float32 *n_float32_ptr = n["vfloat32"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float32_ptr[i],v_float32[i]);
    }

    // float64_array
    n["vfloat64"].set(DataType::float64(10));
    n["vfloat64"].as_float64_array().set(v_float64);
    float64 *n_float64_ptr = n["vfloat64"].value();
    for(size_t i=0;i<10;i++)
    {
        EXPECT_EQ(n_float64_ptr[i],v_float64[i]);
    }

}

//-----------------------------------------------------------------------------
TEST(conduit_array, print_bells_and_whistles)
{
    Node n;

    n["int32_1"].set(DataType::int32(1));
    n["int32_2"].set(DataType::int32(2));

    int32_array va_int32_1 = n["int32_1"].value();
    int32_array va_int32_2 = n["int32_2"].value();

    va_int32_1[0] = 1;

    va_int32_2[0] = 1;
    va_int32_2[1] = 2;

    std::string s_json_int32_1 = va_int32_1.to_json();
    std::string s_json_int32_2 = va_int32_2.to_json();

    std::string s_yaml_int32_1 = va_int32_1.to_yaml();
    std::string s_yaml_int32_2 = va_int32_2.to_yaml();

    std::cout << "int32_1: " << s_json_int32_1 << std::endl;
    std::cout << "int32_2: " << s_json_int32_2 << std::endl;

    EXPECT_EQ(s_json_int32_1,"1");
    EXPECT_EQ(s_json_int32_2,"[1, 2]");

    EXPECT_EQ(s_json_int32_1,s_yaml_int32_1);
    EXPECT_EQ(s_json_int32_2,s_yaml_int32_2);

    std::vector<float64>  v_float64(10,64.0);
    float64_array    va_float64(&v_float64[0],DataType::float64(10));

    std::cout << "to_string(\"yaml\")" << std::endl;
    std::cout << va_float64.to_string("yaml") << std::endl;
    std::cout << "to_string(\"json\")" << std::endl;
    std::cout << va_float64.to_string("json") << std::endl;

    std::cout << "to_json()" << std::endl;
    std::cout << va_float64.to_json() << std::endl;

    std::cout << "to_yaml()" << std::endl;
    std::cout << va_float64.to_yaml() << std::endl;

    std::cout << "to_string_stream(..., yaml)" << std::endl;
    va_float64.to_string_stream(std::cout,"yaml");
    std::cout << std::endl;

    std::cout << "to_string_stream(..., json)" << std::endl;
    va_float64.to_string_stream(std::cout,"json");
    std::cout << std::endl;

    std::cout << "to_json_stream()" << std::endl;
    va_float64.to_json_stream(std::cout);
    std::cout << std::endl;

    std::cout << "to_yaml_stream()" << std::endl;
    va_float64.to_yaml_stream(std::cout);
    std::cout << std::endl;
}

// ccfinderx similar code test start
void ImGui::TableSetBgColor(ImGuiTableBgTarget bg_target, ImU32 color, int column_n)
{
    ImGuiContext& g = *GImGui;
    ImGuiTable* table = g.CurrentTable;
    if (color == IM_COL32_DISABLE)
        color = 0;
    switch (bg_target)
    {
    case ImGuiTableBgTarget_RowBg0_Var:
    case ImGuiTableBgTarget_RowBg1_var:
    {
        if (table->RowPosY1 > table->InnerClipRect.Max.y)
            return;
        int bg_idx = (bg_target == ImGuiTableBgTarget_RowBg1) ? 1 : 0;
        table->RowBgColor[bg_idx] = color;
        break;
    }
    case ImGuiTableBgTarget_CellBg_var:
    {
        if (table->RowPosY1 > table->InnerClipRect.Max.y)
            return;
        if (column_n == -1)
            column_n = table->CurrentColumn;
        if ((table->VisibleMaskByIndex & ((ImU64)1 << column_n)) == 0)
            return;
        if (table->RowCellData[table->RowCellDataCurrent].Column != column_n || table->RowCellDataCurrent < 0)
            table->RowCellDataCurrent++;
        ImGuiTableCellData* cell_data = &table->RowCellData[table->RowCellDataCurrent];
        cell_data->Column = (ImGuiTableColumnIdx)column_n;
        cell_data->BgColor = color;
        break;
    }
    default:
        IM_ASSERT(0);
    }
}
// ccfinderx similar code test end


