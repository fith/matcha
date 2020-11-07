# DO NOT EDIT
# This makefile makes sure all linkable targets are
# up-to-date with anything they link to
default:
	echo "Do not invoke directly"

# Rules to remove targets that are older than anything to which they
# link.  This forces Xcode to relink the targets from scratch.  It
# does not seem to check these dependencies itself.
PostBuild.Matcha.Debug:
/Users/kevin/Scratch/c/matcha/build/cmake-ios-release/bin/Matcha.app/Matcha:
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/bin/Matcha.app/Matcha
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/Matcha.build/Debug/Matcha.build/$(OBJDIR)/arm64/Matcha
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/Matcha.build/Debug/Matcha.build/$(OBJDIR)/x86_64/Matcha


PostBuild.Matcha.Release:
/Users/kevin/Scratch/c/matcha/build/cmake-ios-release/bin/Matcha.app/Matcha:
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/bin/Matcha.app/Matcha
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/Matcha.build/Release/Matcha.build/$(OBJDIR)/arm64/Matcha
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/Matcha.build/Release/Matcha.build/$(OBJDIR)/x86_64/Matcha


PostBuild.Matcha.MinSizeRel:
/Users/kevin/Scratch/c/matcha/build/cmake-ios-release/bin/Matcha.app/Matcha:
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/bin/Matcha.app/Matcha
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/Matcha.build/MinSizeRel/Matcha.build/$(OBJDIR)/arm64/Matcha
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/Matcha.build/MinSizeRel/Matcha.build/$(OBJDIR)/x86_64/Matcha


PostBuild.Matcha.RelWithDebInfo:
/Users/kevin/Scratch/c/matcha/build/cmake-ios-release/bin/Matcha.app/Matcha:
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/bin/Matcha.app/Matcha
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/Matcha.build/RelWithDebInfo/Matcha.build/$(OBJDIR)/arm64/Matcha
	/bin/rm -f /Users/kevin/Scratch/c/matcha/build/cmake-ios-release/Matcha.build/RelWithDebInfo/Matcha.build/$(OBJDIR)/x86_64/Matcha




# For each target create a dummy ruleso the target does not have to exist
