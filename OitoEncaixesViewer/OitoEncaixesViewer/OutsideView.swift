//
//  Outside.swift
//  SeisEncaixesViewer
//
//  Created by Ariadne Bigheti on 21/05/23.
//

import Foundation
import SwiftUI

struct OutsideView: View {
    @EnvironmentObject var viewModel: GymViewModel
    private let adaptativeColumns = [
        GridItem(.adaptive(minimum: 210), alignment: .leading)
    ]
    
    var body: some View {
        HStack {
            if let user = viewModel.userOutsideGym {
                VStack {
                    HStack {
                        Text(user.id)
                        Image(user.imageName)
                            .resizable()
                            .frame(width: 50, height: 50)
                    }
                }
            } else {
                Rectangle()
                    .foregroundColor(.clear)
                    .frame(height: 50)
            }
            Spacer()
        }
        .padding(30)
    }
}
