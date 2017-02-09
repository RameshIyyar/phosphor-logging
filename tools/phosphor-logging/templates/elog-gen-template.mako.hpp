## Note that this file is not auto generated, it is what generates the
## elog-gen.hpp file
// This file was autogenerated.  Do not edit!
// See elog-gen.py for more details
#pragma once

#include <string>
#include <tuple>
#include <type_traits>
#include "log.hpp"

namespace phosphor
{

namespace logging
{

    % for index, name in enumerate(errors):
<%
    namespaces = error_namespace.split('/')
    ## In case someone provided a error_namespace ending with '/', remove the
    ## last split string, which would be an empty string.
    if not namespaces[-1]:
        namespaces = namespaces[:-1]
    classname = name
%>\
    % for s in namespaces:
namespace ${s}
{
    % endfor
namespace _${classname}
{
    % for b in meta[name]:
struct ${b}
{
    static constexpr auto str = "${meta_data[b]['str']}";
    static constexpr auto str_short = "${meta_data[b]['str_short']}";
    using type = std::tuple<std::decay_t<decltype(str)>,${meta_data[b]['type']}>;
    explicit constexpr ${b}(${meta_data[b]['type']} a) : _entry(entry(str, a)) {};
    type _entry;
};
    % endfor

}  // namespace _${classname}
<%
    meta_string = ', '.join(meta[name])
    parent_meta = []

    parent = parents[name]
    while parent:
        parent_meta += [parent + "::" + p for p in meta[parent]]
        parent_meta_short = ', '.join(meta[parent])
        meta_string = meta_string + ", " + parent_meta_short
        parent = parents[parent]
%>
struct ${classname}
{
    static constexpr auto err_code = "${name}";
    static constexpr auto err_msg = "${error_msg[name]}";
    static constexpr auto L = level::${error_lvl[name]};
    % for b in meta[name]:
    using ${b} = _${classname}::${b};
    % endfor
    % for b in parent_meta:
    using ${b.split("::").pop()} = ${b};
    % endfor
    using metadata_types = std::tuple<${meta_string}>;
};
% for s in reversed(namespaces):
} // namespace ${s}
% endfor

    % endfor

} // namespace logging

} // namespace phosphor