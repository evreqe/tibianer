#pragma once

#include <string>

#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_streambuf.hpp>
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>

namespace tb::LibBoost::ZLib
{

static std::string decompressString(const std::string& subject)
{
    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    in.push(boost::iostreams::zlib_decompressor());
    in.push(boost::make_iterator_range(subject));

    std::string decompressed;
    boost::iostreams::copy(in, boost::iostreams::back_inserter(decompressed));

    return decompressed;
}

static void decompressStringEx(const std::string& subject, std::string& buffer)
{
    boost::iostreams::filtering_streambuf<boost::iostreams::input> in;
    in.push(boost::iostreams::zlib_decompressor());
    in.push(boost::make_iterator_range(subject));

    boost::iostreams::copy(in, boost::iostreams::back_inserter(buffer));
}

}
