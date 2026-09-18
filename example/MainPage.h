#pragma once

#pragma once

#include "MainPage.g.h"

namespace winrt::GoldenCarrot::implementation
{
    struct MainPage : MainPageT<MainPage>
    {
        MainPage();

        void OnTileClick(winrt::Windows::Foundation::IInspectable const& sender, winrt::Windows::UI::Xaml::RoutedEventArgs const& e);
    };
}

namespace winrt::GoldenCarrot::factory_implementation
{
    struct MainPage : MainPageT<MainPage, implementation::MainPage>
    {
    };
}