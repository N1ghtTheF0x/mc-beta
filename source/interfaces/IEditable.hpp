#ifndef __MINECRAFT_INTERFACES_IEDITABLE_HPP
#define __MINECRAFT_INTERFACES_IEDITABLE_HPP

#ifdef _DEBUG
#define IEDITABLE(clazz) static void Editor(clazz& item);
#else
#define IEDITABLE(clazz)
#endif

#endif