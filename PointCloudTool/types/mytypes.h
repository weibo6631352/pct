#pragma once
#include <vector>
#include <string>
#include <pcl/point_types.h>
#include <pcl/point_cloud.h>
#include <pcl/PointIndices.h>
#include <pcl/common/impl/common.hpp>
#include "vector3.h"
#include "LeastSquare.h"


namespace pct
{
    typedef struct vegetinfo__
    {
        vegetinfo__() :veget_no(0){};
        vegetinfo__(pcl::PointIndices &in_indices)
            :veget_no(++g_next_no)
        {
            indices = in_indices;
        }
        vegetinfo__(pcl::PointCloud<pcl::PointXYZRGB>::Ptr src_cloud, pcl::PointIndices &in_indices)
            :veget_no(++g_next_no)
        {
            indices = in_indices;

            Eigen::Vector4f fmin_pt;
            Eigen::Vector4f fmax_pt;
            pcl::getMinMax3D(*src_cloud, indices.indices, fmin_pt, fmax_pt);
            min.x = fmin_pt.x();
            min.y = fmin_pt.y();
            min.z = fmin_pt.z();

            max.x = fmax_pt.x();
            max.y = fmax_pt.y();
            max.z = fmax_pt.z();

            cen.x = (min.x + max.x) / 2;
            cen.y = (min.y + max.y) / 2;
            cen.z = (min.z + max.z) / 2;
        }
        pcl::PointIndices indices;
        pcl::PointXYZRGB cen;
        pcl::PointXYZRGB  min;
        pcl::PointXYZRGB  max;

        static unsigned int g_next_no;
        unsigned int veget_no;

        std::string getNo()
        {
            std::string res;
            std::stringstream ss;
            ss << veget_no;
            res += ss.str();

            res += "#veget";
            return res;
        }
    } VegetInfo;
    
    typedef struct lineinfo__
    {
        lineinfo__():begin_tower_no(-1), end_tower_no(-1){};
        enum Asix{ X = 0, Y = 1, Z = 2 };
        Vector3 center;
        Vector3 sta;
        Vector3 end;
        Vector3 v;
        Asix maxAsix;
        std::vector<Vector3> pts;
        std::vector<Vector3> fit_pts;
        pcl::PointIndices indices;
        Fit fit;
        Fit fit_z;
        int begin_tower_no;
        int end_tower_no;
        std::string getLineNo()
        {
            std::string res;
            if (begin_tower_no != -1)
            {
                std::stringstream ss;
                ss << begin_tower_no;
                res += ss.str();
            }
            res += "-";
            if (end_tower_no != -1)
            {
                std::stringstream ss;
                ss << end_tower_no;
                res += ss.str();
            }
            return res;
        }

    } LineInfo;


    typedef struct towerinfo__
    {
        towerinfo__() :tower_no(-1){};
        towerinfo__(pcl::PointIndices &in_indices) 
            :tower_no(-1)
        {
            indices = in_indices;
        }
        pcl::PointIndices indices;
        pcl::PointXYZRGB cen;
        pcl::PointXYZRGB  min;
        pcl::PointXYZRGB  max;

        int tower_no;

        std::string getNo()
        {
            std::string res;
            std::stringstream ss;
            ss << tower_no;
            res += ss.str();
           
            res += "#";
            return res;
        }
    } TowerInfo;
}












#define setsettingitem(itemname, itemtpye, must, def) \
    itemtpye itemname;\
if (vm.count(#itemname)){ \
    std::cout << "[" << #itemname << "]\t" << vm[#itemname].as<itemtpye>() << std::endl;  \
    itemname = vm[#itemname].as<itemtpye>();                        \
}else {         \
    if (must) {\
          std::cout << "����Ĳ�����δ�ҵ�" << #itemname << "ѡ�" << std::endl;           \
          return false;\
                                                            }else{\
            itemname = def;\
                                                            }\
 }\
setting.itemname = itemname;
