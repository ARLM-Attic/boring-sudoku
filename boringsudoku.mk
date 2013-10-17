##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=boringsudoku
ConfigurationName      :=Debug
WorkspacePath          := "/home/kunilkuda/Workspace/boringsudoku"
ProjectPath            := "/home/kunilkuda/Workspace/boringsudoku"
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Daniel Widyanto
Date                   :=10/17/2013
CodeLitePath           :="/home/kunilkuda/.codelite"
LinkerName             :=g++
SharedObjectLinkerName :=g++ -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.o.i
DebugSwitch            :=-gstab
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E 
ObjectsFileList        :="boringsudoku.txt"
PCHCompileFlags        :=
MakeDirCommand         :=mkdir -p
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch)SFML-2.1/include $(IncludeSwitch)include 
IncludePCH             := 
RcIncludePath          := 
Libs                   := $(LibrarySwitch)sfml-audio $(LibrarySwitch)sfml-graphics $(LibrarySwitch)sfml-window $(LibrarySwitch)sfml-system $(LibrarySwitch)sfml-network 
ArLibs                 :=  "sfml-audio" "sfml-graphics" "sfml-window" "sfml-system" "sfml-network" 
LibPath                := $(LibraryPathSwitch). $(LibraryPathSwitch)SFML-2.1/lib 

##
## Common variables
## AR, CXX, CC, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := ar rcus
CXX      := g++
CC       := gcc
CXXFLAGS :=  -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)


##
## User defined environment variables
##
CodeLiteDir:=/usr/share/codelite
LD_LIBRARY_PATH:=$(HOME)/Workspace/sudoku-demo/SFML-2.1/lib
Objects0=$(IntermediateDirectory)/source_main$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

$(IntermediateDirectory)/.d:
	@test -d ./Debug || $(MakeDirCommand) ./Debug

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/source_main$(ObjectSuffix): source/main.cpp $(IntermediateDirectory)/source_main$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "/home/kunilkuda/Workspace/boringsudoku/source/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/source_main$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/source_main$(DependSuffix): source/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/source_main$(ObjectSuffix) -MF$(IntermediateDirectory)/source_main$(DependSuffix) -MM "source/main.cpp"

$(IntermediateDirectory)/source_main$(PreprocessSuffix): source/main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/source_main$(PreprocessSuffix) "source/main.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/source_main$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/source_main$(DependSuffix)
	$(RM) $(IntermediateDirectory)/source_main$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) ".build-debug/boringsudoku"


