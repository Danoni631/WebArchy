#include "pch.h"
#include "MainPage.h"
#include "MainPage.g.cpp"

using namespace winrt;
using namespace Windows::UI::Xaml;

namespace winrt::GoldenCarrot::implementation
{
    MainPage::MainPage()
    {
        InitializeComponent();
    }

    void MainPage::OnTileClick(IInspectable const& sender, RoutedEventArgs const&)
    {
        auto button = sender.as<Controls::Button>();
        winrt::hstring nomeTile = unbox_value<winrt::hstring>(button.Content());
    }
}