-- 
-- @Author: Amélie Heinrich
-- @Create Time: 2024-03-17 12:57:08
-- 

add_rules("mode.debug", "mode.release")

target("PortalMaxxer")
    set_languages("c++17")
    set_rundir(".")
    add_files("src/**.cpp")
    add_includedirs("src", "SFML/include")
    add_linkdirs("SFML/lib")
    add_links("sfml-graphics", "sfml-window", "sfml-system", "sfml-audio")

    if is_mode("debug") then
        set_symbols("debug")
        set_optimize("none")
    end

    if is_mode("release") then
        set_symbols("hidden")
        set_optimize("fastest")
        set_strip("all")
    end    
