# Features of this app example

## Use of a custom QQuickStyle
The style is called here "ModernStyle". It is created by extanding the c++ template of each control in qml (see the Button example). To use it, ```QQuickStyle::setStyle("Modern");``` is called in the main cpp file.

This gives several avantages:
- To use the customized control in QML, there is no need to use some widgets with a specific name; just use the default ```Button```, ```Slider```, ```Menu```, etc. and Qt will use automatically the "ModernStyle" if possible.
- To start, only one control needs to be customized. If a control that is not customized yet is used in QML, Qt will use the default build-in style by default (with Qt6, the style will match the OS). This allow to start creating an app without bothering with the style, and start implementing it little by little later without changing any existing code. E.g: To customize the ```Slider```, simply create a Slider.qml file in the ModernStyle folder, and it will be used everywhere a ```Slider``` is instantiated in QML.
- When customizing a control, as it needs to inherit the c++ templates, it will have no default visual behavior. Hence, to have a functionnal control, it needs to be implemented correctly. As an example, when inherinting the default controls, if the implicitWidth is not defined (even though it should), the implicitWidth will fall back on the one of the default controls. When inheriting the templates, as there is no default qml implementation, if the implicitWidth is not define there will be no fall back value and the control will have a width of 0. So, using the templates, it is mendatory to define by hand the entire qml part of the control and hence understand fully why it works.

One drawback is that the style can not be changed once the app is launched. But, the style here implement a theme option using attached properties (like the Material style do). The app theme can then be set from ```Light``` to ```Dark``` during runtime. This allow for plenty of room for customization, and make it possible to add support for user provided theme later.

## Theme option using attached properties
The usage of attached properties (defined in ModernStyle.hpp and ModernStyle.cpp) allow to propagate the ```Modern.theme``` property to all children of the Item. Hence, if the theme is changed in the root of the app, the whole app will be updated accordingly.
Furthermore, it is still possible to force one specific Item (and all its children) to use a specific theme by setting explicitly the ```Modern.style``` attached property for this Item.
One drawback of using attached properties is that every Item in QML will have a copy of the full cpp attached property. This can be improved later with some shared attached properties using smart pointer later.

## Size values are semi hard-coded in QML
The size values are more or less all the numeric values like width, height, paddings, margins, radius, etc. These are set for each control in the related QML file. E.g: The default width of the Button, is set in ```Button.qml```.
To still provide a way to scale the controls to the size of the screen or to a custom value, theses size values go through a scaling function defined in ModernStyleSingleton.qml.
```wscale(size)``` is used to scale the value given the width of the screen, and ```hscale(size)``` is used to scale the value given the height of the screen. A third function is used to mean the hscale and the wscale. This is update dynamically as soon as the Window of the app move to a different screen. This allow the app widgets to have the same physical size for two different screens of the same physical size but different resolution (E.g: a FullHD monitor and a UHD monitor).
If a custom value value is set (E.g: multiply all size by 1.5), the height and width of the screen will be ignore.
