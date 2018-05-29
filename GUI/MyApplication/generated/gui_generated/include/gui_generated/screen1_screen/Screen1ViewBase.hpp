/*********************************************************************************/
/********** THIS FILE IS GENERATED BY TOUCHGFX DESIGNER, DO NOT MODIFY ***********/
/*********************************************************************************/
#ifndef SCREEN1_VIEW_BASE_HPP
#define SCREEN1_VIEW_BASE_HPP

#include <gui/common/FrontendApplication.hpp>
#include <mvp/View.hpp>
#include <gui/screen1_screen/Screen1Presenter.hpp>
#include <touchgfx/widgets/Box.hpp>
#include <touchgfx/containers/ScrollableContainer.hpp>
#include <touchgfx/containers/Container.hpp>
#include <touchgfx/widgets/ScalableImage.hpp>
#include <touchgfx/widgets/TextArea.hpp>
#include <touchgfx/widgets/ButtonWithIcon.hpp>

class Screen1ViewBase : public touchgfx::View<Screen1Presenter>
{
public:
    Screen1ViewBase();
    virtual ~Screen1ViewBase() {}

protected:
    FrontendApplication& application() { 
        return *static_cast<FrontendApplication*>(Application::getInstance()); 
    }

    /*
     * Member Declarations
     */
    touchgfx::Box background;
    touchgfx::Box listBackground;
    touchgfx::ScrollableContainer listContainer;
    touchgfx::Box productBackground;
    touchgfx::Container productContainer;
    touchgfx::ScalableImage productImage;
    touchgfx::TextArea productQuantity;
    touchgfx::TextArea productDescription;
    touchgfx::ButtonWithIcon buttonWithIcon1;
    touchgfx::Box optionsBackground;
    touchgfx::Container optionsContainer;
    touchgfx::Box separatorVertical1;
    touchgfx::Box separatorVertical2;

private:

};

#endif // SCREEN1_VIEW_BASE_HPP