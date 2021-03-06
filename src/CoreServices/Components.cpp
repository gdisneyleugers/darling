#include "Components.h"
#include "ComponentsInternal.h"
#include <AudioUnit/AUComponent.h>
#include <AudioUnit/AUComponentInternal.h>
#include <CoreServices/MacErrors.h>

Component FindNextComponent(Component prev, ComponentDescription* desc)
{
	if ((desc->componentType & 0xffff0000) == kComponentTypeAudioUnit)
	{
		return AudioComponentFindNext((AudioComponent) prev, (AudioComponentDescription*) desc);
	}
	else
		return nullptr;
}

long CountComponents(ComponentDescription* desc)
{
	if ((desc->componentType & 0xffff0000) == kComponentTypeAudioUnit)
	{
		return AudioComponentCount((AudioComponentDescription*) desc);
	}
	else
		return 0;
}

OSErr OpenAComponent(Component comp, ComponentInstance* out)
{
	if (!out)
		return paramErr;

	*out = nullptr;

	if (GetComponentType(comp) == kComponentTypeAudioUnit)
	{
		AudioComponentInstance inst;
		OSErr err;

		err = AudioComponentInstanceNew((AudioComponent) comp, &inst);

		*out = inst;
		return err;
	}
	else
		return unimpErr;
}

ComponentInstance OpenComponent(Component comp)
{
	ComponentInstance inst;
	OpenAComponent(comp, &inst);
	return inst;
}

OSErr CloseComponent(ComponentInstance inst)
{
	delete inst;
	return noErr;
}

