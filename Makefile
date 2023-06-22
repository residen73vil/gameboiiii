#
# A Makefile that compiles all .c and .s files in "src" and "res" 
# subdirectories and places the output in a "obj" subdirectory
#

# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
$(info buildsystem = $(shell uname | cut -d "-" -f 1))
ifeq ($(shell uname | cut -d "-" -f 1 ), MINGW64_NT)
    GBDK_HOME = C:/PortableApps/gbdk/
else ifeq ($(shell uname | cut -d "-" -f 1 ), MSYS_NT)
    GBDK_HOME = G:/2/gbdk/
else
    GBDK_HOME = ../../
endif

LCC = $(GBDK_HOME)bin/lcc 
PNG2ASSET = $(GBDK_HOME)bin/png2asset
TEXT2ASSET = tools/text2tile_addreses.py

# You can set flags for LCC here
# For example, you can uncomment the line below to turn on debug output
# LCCFLAGS = -debug

# You can set the name of the .gb ROM file here
PROJECTNAME    = beast

SRCDIR      = src
OBJDIR      = obj
RESDIR      = res
ASSETS      = assets
RESOBJSRC   = obj/res
IMGPNGS     = $(foreach dir,$(ASSETS),$(notdir $(wildcard $(dir)/*.png)))
TEXTASSETS     = $(foreach dir,$(ASSETS),$(notdir $(wildcard $(dir)/*.txt)))
IMGSOURCES  = $(IMGPNGS:%.png=$(RESOBJSRC)/%.c)
TEXTASSETSSOURSES = $(TEXTASSETS:%.txt=$(RESOBJSRC)/%.h)
IMGOBJS     = $(IMGSOURCES:$(RESOBJSRC)/%.c=$(OBJDIR)/%.o)
BINS	    = $(OBJDIR)/$(PROJECTNAME).gb
CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c))) $(foreach dir,$(RESDIR),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES  = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS       = $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)


all:	prepare $(BINS)


$(RESOBJSRC)/%.c:	$(ASSETS)/%.png
	$(PNG2ASSET) $< -spr8x8 -tiles_only -c $@

$(RESOBJSRC)/%.h:	$(ASSETS)/%.txt
	$(TEXT2ASSET)  $< $(RESOBJSRC)/


compile.bat: Makefile
	@echo "REM Automatically generated from Makefile" > compile.bat
	@make -sn | sed y/\\//\\\\/ | grep -v make >> compile.bat

# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.c 
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .c files in "res/" to .o object files
$(OBJDIR)/%.o:	$(RESDIR)/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

$(OBJDIR)/%.o:	$(RESOBJSRC)/%.c
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.s
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# If needed, compile .c files in "src/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJDIR)/%.s:	$(SRCDIR)/%.c
	$(LCC) $(LCCFLAGS) -S -o $@ $<

# Link the compiled object files into a .gb ROM file
$(BINS):	$(OBJS)
	$(LCC) $(LCCFLAGS) -o $(BINS) $(IMGOBJS) $(OBJS)

$(IMGOBJS): $(IMGSOURCES)
	$(LCC) $(LCCFLAGS) -c -o $@ $<

$(RESDIR)/%.o: $(RESOBJSRC)/%.c 

$(OBJS):	$(IMGOBJS) $(TEXTASSETSSOURSES)

prepare: 
	mkdir -p $(OBJDIR) $(RESOBJSRC) 

clean:
#	rm -f  *.gb *.ihx *.cdb *.adb *.noi *.map
	rm -f  $(OBJDIR)/*.*
	rm -f  $(RESOBJSRC)/*.*
	rm -rf  $(RESOBJSRC)


