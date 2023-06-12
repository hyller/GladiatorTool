#!/usr/bin/python
# -*- coding: UTF-8 -*-

# Pythom DOM 使用
# 节点类型:
# ELEMENT_NODE（元素节点）：1.中的<users></users> 或者 <address></address>等
# TEXT_NODE（标签中的内容）：1.中的标签的内容admin@qq.com
# ATTRIBUTE_NODE（标签属性）：1.中的id="1"
#
# 取值方式:
# ELEMENT_NODE：xxx.getElementsByTagName('tag_name') 拿到的值是一个列表，xxx是父标签
# TEXT_NODE：xxx.firstChild.data 从标签内容中取出值，但一般xxx都是通过getElementsByTagName获取到的，所以会写成xxx[0]
# ATTRIBUTE_NODE：xxx.attributes['id'].value，xxx就是通过getElementsByTagName获取到的标签
#
# 所以总的来说，不管有多少层嵌套标签，取值方式就三种，1.如果获取标签信息，就使用xxx.getElementsByTagName('xx')，2.如果获取属性信息，就用xxx.attributes['xx'].value，3.如果获取标签内容，就用firstChild.data

# Exact locationURI element from .project
# Usage: make sure you have .project

from xml.dom.minidom import parse
import xml.dom.minidom
import glob
import os

sdk_path = "C:/Users/sesa280753/SimplicityStudio/SDKs/gecko_sdk-4.2.x/"

# 使用minidom解析器打开 XML 文档
DOMTree = xml.dom.minidom.parse(".project")
collection = DOMTree.documentElement

# 在集合中获取所有locationURI
urls = collection.getElementsByTagName("locationURI")

# 打印locationURI的详细信息, 找出source文件
for url in urls:
    print(url.firstChild.data.replace("STUDIO_SDK_LOC/", sdk_path))


# 使用minidom解析器打开 .cproject 文档
DOMTree = xml.dom.minidom.parse(".cproject")
collection = DOMTree.documentElement

# 在集合中获取所有option
options = collection.getElementsByTagName("option")

# 打印Include paths (-I)的详细信息，找出header文件
for option in options:
    if option.attributes['name'].value == "Include paths (-I)":
        paths = option.getElementsByTagName("listOptionValue")
        for path in paths:
            path_txt = path.attributes['value'].value.replace(
                "${StudioSdkPath}", sdk_path)
            path_txt = eval(path_txt) + "/*.h"
            c_headers = glob.glob(path_txt)
            for c_header in c_headers:
                print(c_header)
        break


# 列出当前目录文件
files = glob.glob(os.getcwd() + "/*.c")
for file in files:
    print(file)
files = glob.glob(os.getcwd() + "/*.h")
for file in files:
    print(file)
