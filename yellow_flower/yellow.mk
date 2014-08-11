##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Release
ProjectName            :=yellow
ConfigurationName      :=Release
WorkspacePath          := "C:\Users\Gustavo\Documents\My Dropbox\Public\little_flower"
ProjectPath            := "C:\Users\Gustavo\Documents\My Dropbox\Public\little_flower\yellow"
IntermediateDirectory  :=./Release
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Gustavo
Date                   :=08/11/14
CodeLitePath           :="C:\Program Files (x86)\CodeLite"
LinkerName             :=C:\MinGW-4.8.1\bin\g++.exe 
SharedObjectLinkerName :=C:\MinGW-4.8.1\bin\g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=$(PreprocessorSwitch)NDEBUG 
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="yellow.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:\MinGW-4.8.1\bin\windres.exe 
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:\MinGW-4.8.1\bin\ar.exe rcu
CXX      := C:\MinGW-4.8.1\bin\g++.exe 
CC       := C:\MinGW-4.8.1\bin\gcc.exe 
CXXFLAGS := -std=c++1y -O3 -Wall $(Preprocessors)
CFLAGS   :=  -O3 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:\MinGW-4.8.1\bin\as.exe 


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files (x86)\CodeLite
UNIT_TEST_PP_SRC_DIR:=C:\UnitTest++-1.3
Objects0=$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IntermediateDirectory)/test_lru.cpp$(ObjectSuffix) $(IntermediateDirectory)/first_try.cpp$(ObjectSuffix) 



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
	@$(MakeDirCommand) "./Release"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/main.cpp$(ObjectSuffix): main.cpp $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Gustavo/Documents/My Dropbox/Public/little_flower/yellow/main.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/main.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/main.cpp$(DependSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/main.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/main.cpp$(DependSuffix) -MM "main.cpp"

$(IntermediateDirectory)/main.cpp$(PreprocessSuffix): main.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix) "main.cpp"

$(IntermediateDirectory)/test_lru.cpp$(ObjectSuffix): test_lru.cpp $(IntermediateDirectory)/test_lru.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Gustavo/Documents/My Dropbox/Public/little_flower/yellow/test_lru.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/test_lru.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/test_lru.cpp$(DependSuffix): test_lru.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/test_lru.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/test_lru.cpp$(DependSuffix) -MM "test_lru.cpp"

$(IntermediateDirectory)/test_lru.cpp$(PreprocessSuffix): test_lru.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/test_lru.cpp$(PreprocessSuffix) "test_lru.cpp"

$(IntermediateDirectory)/first_try.cpp$(ObjectSuffix): first_try.cpp $(IntermediateDirectory)/first_try.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Gustavo/Documents/My Dropbox/Public/little_flower/yellow/first_try.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/first_try.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/first_try.cpp$(DependSuffix): first_try.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/first_try.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/first_try.cpp$(DependSuffix) -MM "first_try.cpp"

$(IntermediateDirectory)/first_try.cpp$(PreprocessSuffix): first_try.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/first_try.cpp$(PreprocessSuffix) "first_try.cpp"


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) $(IntermediateDirectory)/main.cpp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/main.cpp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/main.cpp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/test_lru.cpp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/test_lru.cpp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/test_lru.cpp$(PreprocessSuffix)
	$(RM) $(IntermediateDirectory)/first_try.cpp$(ObjectSuffix)
	$(RM) $(IntermediateDirectory)/first_try.cpp$(DependSuffix)
	$(RM) $(IntermediateDirectory)/first_try.cpp$(PreprocessSuffix)
	$(RM) $(OutputFile)
	$(RM) $(OutputFile).exe
	$(RM) "../.build-release/yellow"


